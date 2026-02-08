import { Component, inject, OnInit } from "@angular/core";
import { CommonModule } from "@angular/common";
import { Router } from "@angular/router";
import { FormBuilder, FormGroup, ReactiveFormsModule, Validators } from "@angular/forms";

import { ButtonComponent } from "../../../../component";
import { InputFieldComponent } from "../../../../component";
import { PanelComponent } from "../../../../component";

import { StatusCircleComponent } from "../status-circle/status-circle.component";

import { AuthService } from "../../../../service/auth.service";
import { APIService } from "../../../../service/api.service";
import { ServerService } from "../../../../service/server.service";

@Component({
    selector: "app-login-panel",
    templateUrl: "./login-panel.component.html",
    styleUrls: ["./login-panel.component.scss"],
    imports: [
        CommonModule,
        ReactiveFormsModule,
        PanelComponent,
        InputFieldComponent,
        ButtonComponent,
        StatusCircleComponent,
    ],
})

export class LoginPanel implements OnInit {
    router = inject(Router);
    private formbuilder = inject(FormBuilder);
    private apiService = inject(APIService);
    private serverService = inject(ServerService);
    private authService = inject(AuthService);

    formServer: FormGroup;
    formLogin: FormGroup;
    status: 'online' | 'offline' | 'loading' | 'error' | 'unknown' = 'offline';
    error: string | null = null;

    constructor() {
        const server = this.serverService.getServer();
        this.formServer = this.formbuilder.group({
            ip: [server?.address || '', Validators.required],
            port: [server?.port || '', Validators.required],
        });

        if (server) {
            this.status = 'loading';
        }

        this.formLogin = this.formbuilder.group({
            username: ['', Validators.required],
            password: ['', Validators.required]
        });
    }

    ngOnInit(): void {
        if (this.serverService.getServer()) {
            this.checkStatus();
        }
    }

    async checkStatus(): Promise<void> {
        try {
            await this.apiService.getStatus();
            this.status = 'online';
        } catch {
            this.status = 'error';
        }
    }

    async checkStatusWithParams(ip: string, port: string): Promise<boolean> {
        try {
            const cleanedIp = ip.replace(/^https?:\/\//, '');
            const response = await fetch(`http://${cleanedIp}:${port}/status`);
            if (!response.ok) throw new Error();
            this.status = 'online';
            return true;
        } catch {
            this.status = 'error';
            return false;
        }
    }

    async handleServer(): Promise<void> {
        this.error = null;
        this.status = 'loading';

        const { ip, port } = this.formServer.value;
        const ok = await this.checkStatusWithParams(ip, port);

        if (!ok) {
            this.error = 'Could not connect to the server.';
            return;
        }

        this.serverService.connect(ip, port);
    }

    async handleLogin() {
        if (this.formLogin.invalid) {
            return;
        }
        this.error = null;

        const { username, password } = this.formLogin.value;

        try {
            const loginResponse = await this.apiService.postData<any>('/login', { username, password });

            if (!loginResponse?.sessionID || !loginResponse?.userID) {
                throw new Error('Invalid login response');
            }

            this.authService.login(loginResponse.userID, loginResponse.username, loginResponse.sessionID);
            this.router.navigate(['/account']);

        } catch (err: any) {
            console.error('Login failed:', err);
            this.error = err.message || 'Login failed.';
        }
    }

    async handleRegister(): Promise<void> {
        if (this.formLogin.invalid) {
            return;
        }

        this.error = null;

        const { username, password } = this.formLogin.value;

        try {
            const registerResponse =
                await this.apiService.postData<any>('/sign', { username, password });

            if (!registerResponse?.sessionID || !registerResponse?.userID) {
                throw new Error('Invalid register response');
            }

            this.authService.login(registerResponse.userID, registerResponse.username, registerResponse.sessionID);

            this.router.navigate(['/account']);

        } catch (err: any) {
            console.error('Register failed:', err);
            this.error = err.message || 'Register failed.';
        }
    }
}