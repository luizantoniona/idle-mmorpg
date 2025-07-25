import { StorageManager } from "./StorageManager";

export interface AuthData {
    userID: number;
    username: string;
    sessionID: string;
}

const STORAGE_KEY = "auth";

export class AuthManager {
    static get(): AuthData | null {
        return StorageManager.get<AuthData>(STORAGE_KEY, sessionStorage);
    }

    static login(data: AuthData): void {
        StorageManager.set(STORAGE_KEY, data, sessionStorage);
    }

    static logout(): void {
        StorageManager.remove(STORAGE_KEY, sessionStorage);
    }
}
