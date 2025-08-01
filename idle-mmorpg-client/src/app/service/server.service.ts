import { Injectable } from '@angular/core';
import { BehaviorSubject, Observable } from 'rxjs';
import { ServerData, ServerManager } from '../manager/server.manager';

@Injectable({
    providedIn: 'root',
})
export class ServerService {
    private serverSubject: BehaviorSubject<ServerData | null>;
    server$: Observable<ServerData | null>;

    constructor(private serverManager: ServerManager) {
        const initialData = this.serverManager.get();
        this.serverSubject = new BehaviorSubject<ServerData | null>(initialData);
        this.server$ = this.serverSubject.asObservable();
    }

    connect(address: string, port: string): void {
        const data = { address, port };
        this.serverManager.connect(data);
        this.serverSubject.next(data);
    }

    disconnect(): void {
        this.serverManager.disconnect();
        this.serverSubject.next(null);
    }

    getAddress(): string | null {
        return this.serverSubject.value?.address ?? null;
    }

    getPort(): string | null {
        return this.serverSubject.value?.port ?? null;
    }

    getServer(): ServerData | null {
        return this.serverSubject.value;
    }
}
