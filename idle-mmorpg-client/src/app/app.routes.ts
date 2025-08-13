import { Routes } from "@angular/router";

import { AccountPage } from "./pages/account/account.page";
import { GamePage } from "./pages/game/game.page";
import { LoginPage } from "./pages/login/login.page";

export const routes: Routes = [
    { path: "", component: LoginPage },
    { path: "account", component: AccountPage },
    { path: "game", component: GamePage },
];
