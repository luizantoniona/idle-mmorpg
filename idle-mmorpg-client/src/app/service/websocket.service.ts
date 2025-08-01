import { Injectable, OnDestroy } from '@angular/core';
import { Subject, Observable } from 'rxjs';
import { ServerManager } from '../manager/server.manager';
import { AuthManager } from '../manager/auth.manager';

type ConnectionStatus = 'connecting' | 'connected' | 'disconnected' | 'error';

@Injectable({
    providedIn: 'root',
})
export class WebsocketService implements OnDestroy {
    private socket: WebSocket | null = null;
    private currentUrl: string | null = null;

    private messageSubject = new Subject<any>();
    private statusSubject = new Subject<ConnectionStatus>();

    public messages$: Observable<any> = this.messageSubject.asObservable();
    public status$: Observable<ConnectionStatus> = this.statusSubject.asObservable();

    constructor(
        private serverManager: ServerManager,
        private authManager: AuthManager
    ) { }

    connect(characterId: number): void {
        const server = this.serverManager.get();
        const auth = this.authManager.get();

        if (!server) {
            throw new Error('No server configured');
        }

        if (!auth?.sessionID) {
            throw new Error('User not authenticated');
        }

        const wsUrl = `ws://${server.address}:${server.port}/ws/character?sid=${auth.sessionID}&character=${characterId}`;

        if (this.socket && this.currentUrl === wsUrl && this.socket.readyState === WebSocket.OPEN) {
            console.warn('WebSocket already connected.');
            return;
        }

        this.currentUrl = wsUrl;
        this.statusSubject.next('connecting');

        this.socket = new WebSocket(wsUrl);

        this.socket.onopen = () => {
            console.log('WebSocket connected:', wsUrl);
            this.statusSubject.next('connected');
        };

        this.socket.onmessage = (event) => {
            try {
                const data = JSON.parse(event.data);
                this.messageSubject.next(data);
            } catch (err) {
                console.error('Message parse error:', err);
            }
        };

        this.socket.onclose = (event) => {
            console.warn('WebSocket closed:', event);
            this.socket = null;
            this.statusSubject.next('disconnected');
        };

        this.socket.onerror = (event) => {
            console.error('WebSocket error:', event);
            this.statusSubject.next('error');
        };
    }

    send(data: any): void {
        if (this.socket?.readyState === WebSocket.OPEN) {
            this.socket.send(JSON.stringify(data));
        } else {
            console.warn('Attempting to send with WebSocket closed.');
        }
    }

    close(): void {
        if (this.socket) {
            this.socket.close();
        }
        this.socket = null;
        this.statusSubject.next('disconnected');
    }

    isConnected(): boolean {
        return this.socket?.readyState === WebSocket.OPEN;
    }

    ngOnDestroy(): void {
        this.close();
        this.messageSubject.complete();
        this.statusSubject.complete();
    }
}
