import { Component, inject, OnInit } from "@angular/core";
import { CommonModule } from "@angular/common";
import { Router } from "@angular/router";
import { FormBuilder, FormGroup, ReactiveFormsModule, Validators } from "@angular/forms";

import { ButtonComponent, InputFieldComponent, PanelComponent } from "../../../../component/ui";

import { StatusCircleComponent } from "../status-circle/status-circle.component";

import { AuthService, APIService, ServerService } from "../../../../service/";

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
    errorServer: string | null = null;
    errorLogin: string | null = null;

    constructor() {
        const server = this.serverService.getServer();

        this.formServer = this.formbuilder.group({
            baseUrl: [server?.baseUrl || '', Validators.required],
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

    private normalizeUrl(url: string): string {
        let normalized = url.trim();

        // TODO: In the future, we can change the server API to use https: or http: as prefix
        // TODO: We need to handle both http or https

        if (!normalized.startsWith('http://') && !normalized.startsWith('https://')) {
            normalized = `http://${normalized}`;
        }

        return normalized.replace(/\/+$/, '');
    }

    async checkStatus(): Promise<void> {
        try {
            await this.apiService.getStatus();
            this.status = 'online';
        } catch {
            this.status = 'error';
        }
    }

    async checkStatusWithParams(baseUrl: string): Promise<boolean> {
        try {
            const normalized = this.normalizeUrl(baseUrl);

            const response = await fetch(`${normalized}/status`);
            if (!response.ok) {
                throw new Error();
            }

            this.status = 'online';
            return true;

        } catch {
            this.status = 'error';
            return false;
        }
    }

    async handleServer(): Promise<void> {
        this.errorServer = null;
        this.status = 'loading';

        const { baseUrl } = this.formServer.value;

        const ok = await this.checkStatusWithParams(baseUrl);

        if (!ok) {
            this.errorServer = 'Could not connect to the server.';
            return;
        }

        const normalized = this.normalizeUrl(baseUrl);
        this.serverService.connect(normalized);
    }

    async handleLogin() {
        if (this.formLogin.invalid) {
            return;
        }

        this.errorLogin = null;

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
            this.errorLogin = 'Login failed.';
        }
    }

    async handleRegister(): Promise<void> {
        if (this.formLogin.invalid) {
            return;
        }

        this.errorLogin = null;

        const { username, password } = this.formLogin.value;

        try {
            const registerResponse = await this.apiService.postData<any>('/sign', { username, password });

            if (!registerResponse?.sessionID || !registerResponse?.userID) {
                throw new Error('Invalid register response');
            }

            this.authService.login(registerResponse.userID, registerResponse.username, registerResponse.sessionID);
            this.router.navigate(['/account']);

        } catch (err: any) {
            console.error('Register failed:', err);
            this.errorLogin = 'Register failed.';
        }
    }
}