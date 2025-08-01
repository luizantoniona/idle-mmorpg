import { Injectable } from '@angular/core';

import { StorageManager } from './storage.manager';

export interface ServerData {
    address: string;
    port: string;
}

const STORAGE_KEY = 'server';

@Injectable({
    providedIn: 'root',
})

export class ServerManager {
    get(): ServerData | null {
        return StorageManager.get<ServerData>(STORAGE_KEY);
    }

    connect(data: ServerData): void {
        StorageManager.set(STORAGE_KEY, data);
    }

    disconnect(): void {
        StorageManager.remove(STORAGE_KEY);
    }
}
