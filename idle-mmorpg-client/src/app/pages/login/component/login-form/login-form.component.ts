import { Component, inject } from '@angular/core';
import { FormBuilder, ReactiveFormsModule, Validators } from '@angular/forms';
import { Router } from '@angular/router';
import { CommonModule } from '@angular/common';
import { PanelVerticalComponent } from '../../../../component/panel/panel-vertical.component';
import { InputFieldComponent } from '../../../../component/input-field/input-field.component';
import { ButtonComponent } from '../../../../component/button/button.component';
import { AuthService } from '../../../../service/auth.service';
import { APIService } from '../../../../service/api.service';

@Component({
    selector: 'app-login-form',
    standalone: true,
    imports: [
        CommonModule,
        ReactiveFormsModule,
        PanelVerticalComponent,
        InputFieldComponent,
        ButtonComponent
    ],
    templateUrl: './login-form.component.html',
    styleUrls: ['./login-form.component.scss']
})
export class LoginFormComponent {
    fb = inject(FormBuilder);
    authService = inject(AuthService);
    router = inject(Router);
    form = this.fb.group({
        username: ['', Validators.required],
        password: ['', Validators.required]
    });
    error: string | null = null;

    apiService = inject(APIService);

    async handleSubmit() {
        if (this.form.invalid) return;
        this.error = null;

        const { username, password } = this.form.value;

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
}