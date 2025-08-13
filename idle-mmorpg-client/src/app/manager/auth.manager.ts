import { Injectable } from "@angular/core";

import { StorageManager } from "./storage.manager";

export interface AuthData {
    userID: number;
    username: string;
    sessionID: string;
}

const STORAGE_KEY = "auth";

@Injectable({
    providedIn: "root",
})

export class AuthManager {
    get(): AuthData | null {
        return StorageManager.get<AuthData>(STORAGE_KEY, sessionStorage);
    }

    login(data: AuthData): void {
        StorageManager.set(STORAGE_KEY, data, sessionStorage);
    }

    logout(): void {
        StorageManager.remove(STORAGE_KEY, sessionStorage);
    }
}
