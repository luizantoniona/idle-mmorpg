import { Component } from '@angular/core';
import { ServerFormComponent } from './component/server-form/server-form.component';
import { LoginFormComponent } from './component/login-form/login-form.component';
import { CommonModule } from '@angular/common';

@Component({
    selector: 'app-login-page',
    standalone: true,
    imports: [
        CommonModule,
        ServerFormComponent,
        LoginFormComponent,
    ],
    templateUrl: './login.page.html',
    styleUrls: ['./login.page.scss']
})
export class LoginPage { }