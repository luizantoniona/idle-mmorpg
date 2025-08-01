import { Routes } from '@angular/router';
import { LoginPage } from './pages/login/login.page';
import { AccountPage } from './pages/account/account.page';

export const routes: Routes = [
    { path: '', component: LoginPage },
    { path: 'account', component: AccountPage },
];
