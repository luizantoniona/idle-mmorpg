import { Component } from "@angular/core";
import { CommonModule } from "@angular/common";

import { LoginPanel } from "./component/login-panel/login-panel.component";

@Component({
    selector: "app-login-page",
    templateUrl: "./login.page.html",
    styleUrls: ["./login.page.scss"],
    imports: [
        CommonModule,
        LoginPanel,
    ],
})

export class LoginPage { }