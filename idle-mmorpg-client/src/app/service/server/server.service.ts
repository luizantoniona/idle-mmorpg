import { Injectable } from "@angular/core";
import { BehaviorSubject, Observable } from "rxjs";

import { ServerData, ServerManager } from "../../manager";

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

    connect(baseUrl: string): void {
        const normalized = this.normalizeUrl(baseUrl);

        const data = { baseUrl: normalized };
        this.serverManager.connect(data);
        this.serverSubject.next(data);
    }

    disconnect(): void {
        this.serverManager.disconnect();
        this.serverSubject.next(null);
    }

    getBaseUrl(): string | null {
        return this.serverSubject.value?.baseUrl ?? null;
    }

    getServer(): ServerData | null {
        return this.serverSubject.value;
    }

    private normalizeUrl(url: string): string {
        if (!url.startsWith('http://') && !url.startsWith('https://')) {
            return `http://${url}`;
        }
        return url;
    }
}
