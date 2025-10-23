import { Component } from "@angular/core";
import { CommonModule } from "@angular/common";

import { ServerFormComponent } from "./component/server-form/server-form.component";
import { LoginFormComponent } from "./component/login-form/login-form.component";

@Component({
    selector: "app-login-page",
    templateUrl: "./login.page.html",
    styleUrls: ["./login.page.scss"],
    imports: [
        CommonModule,
        ServerFormComponent,
        LoginFormComponent,
    ],
})

export class LoginPage { }