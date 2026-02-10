import { Routes } from "@angular/router";

import { AccountPage, GamePage, LoginPage } from "./pages/";

export const routes: Routes = [
    { path: "", component: LoginPage },
    { path: "account", component: AccountPage },
    { path: "game", component: GamePage },
];
