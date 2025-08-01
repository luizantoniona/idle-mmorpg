import { Injectable } from '@angular/core';
import { BehaviorSubject, Observable } from 'rxjs';
import { AuthData, AuthManager } from '../manager/auth.manager';
import { APIService } from './api.service';

@Injectable({
    providedIn: 'root',
})
export class AuthService {
    private authSubject: BehaviorSubject<AuthData | null>;
    auth$: Observable<AuthData | null>;

    constructor(
        private authManager: AuthManager,
        private api: APIService
    ) {
        const initial = this.authManager.get();
        this.authSubject = new BehaviorSubject<AuthData | null>(initial);
        this.auth$ = this.authSubject.asObservable();

        if (initial?.sessionID) {
            this.api.setAuthToken(initial.sessionID);
        }
    }

    login(userID: number, username: string, sessionID: string): void {
        const data: AuthData = { userID, username, sessionID };
        this.authManager.login(data);
        this.api.setAuthToken(sessionID);
        this.authSubject.next(data);
    }

    logout(): void {
        this.authManager.logout();
        this.api.clearAuthToken();
        this.authSubject.next(null);
    }

    isLoggedIn(): boolean {
        return !!this.authSubject.value?.sessionID;
    }

    getUserId(): number | null {
        return this.authSubject.value?.userID ?? null;
    }

    getUsername(): string | null {
        return this.authSubject.value?.username ?? null;
    }

    getSessionId(): string | null {
        return this.authSubject.value?.sessionID ?? null;
    }

    getAuth(): AuthData | null {
        return this.authSubject.value;
    }
}
