import { StorageManager } from "./StorageManager";

export interface ServerData {
    address: string;
    port: string;
}

const STORAGE_KEY = "server";

export class ServerManager {
    static get(): ServerData | null {
        return StorageManager.get<ServerData>(STORAGE_KEY);
    }

    static connect(data: ServerData): void {
        StorageManager.set(STORAGE_KEY, data);
    }

    static disconnect(): void {
        StorageManager.remove(STORAGE_KEY);
    }
}
