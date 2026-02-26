import { Component } from "@angular/core";
import { CommonModule } from "@angular/common";

import { ImageComponent } from "../../component/ui";

import { LoginPanel } from "./component/login-panel/login-panel.component";

@Component({
    selector: "app-login-page",
    templateUrl: "./login.page.html",
    styleUrls: ["./login.page.scss"],
    imports: [
        CommonModule,
        ImageComponent,
        LoginPanel,
    ],
})

export class LoginPage { }