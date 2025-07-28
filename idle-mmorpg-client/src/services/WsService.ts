import { ServerManager } from "../managers/ServerManager";
import { AuthManager } from "../managers/AuthManager";

type MessageCallback = (data: any) => void;
type StatusCallback = (status: "connecting" | "connected" | "disconnected" | "error") => void;

export class WsService {
    private socket: WebSocket | null = null;
    private messageCallbacks: MessageCallback[] = [];
    private statusCallbacks: StatusCallback[] = [];

    private currentUrl: string | null = null;

    connect(characterId: number): void {
        const server = ServerManager.get();
        const auth = AuthManager.get();

        if (!server) {
            throw new Error("No server configured");
        }

        if (!auth?.sessionID) {
            throw new Error("User not authenticated");
        }

        const wsUrl = `ws://${server.address}:${server.port}/ws/character?sid=${auth.sessionID}&character=${characterId}`;

        if (this.socket && this.currentUrl === wsUrl && this.socket.readyState === WebSocket.OPEN) {
            console.warn("WebSocket already connected.");
            return;
        }

        this.currentUrl = wsUrl;
        this.notifyStatus("connecting");

        this.socket = new WebSocket(wsUrl);

        this.socket.onopen = () => {
            console.log("Connected:", wsUrl);
            this.notifyStatus("connected");
        };

        this.socket.onmessage = (event) => {
            try {
                const data = JSON.parse(event.data);
                this.messageCallbacks.forEach((cb) => cb(data));
            } catch (err) {
                console.error("Message parse error:", err);
            }
        };

        this.socket.onclose = (event) => {
            console.warn("WebSocket closed:", event);
            this.socket = null;
            this.notifyStatus("disconnected");
        };

        this.socket.onerror = (event) => {
            console.error("Error WebSocket:", event);
            this.notifyStatus("error");
        };
    }

    send(data: any): void {
        if (this.socket?.readyState === WebSocket.OPEN) {
            this.socket.send(JSON.stringify(data));
        } else {
            console.warn("Tentando enviar com WebSocket fechado.");
        }
    }

    onMessage(callback: MessageCallback): void {
        this.messageCallbacks.push(callback);
    }

    onStatusChange(callback: StatusCallback): void {
        this.statusCallbacks.push(callback);
    }

    private notifyStatus(status: Parameters<StatusCallback>[0]) {
        this.statusCallbacks.forEach((cb) => cb(status));
    }

    close(): void {
        if (this.socket) {
            this.socket.close();
        }
        this.socket = null;
        this.notifyStatus("disconnected");
    }

    isConnected(): boolean {
        return this.socket?.readyState === WebSocket.OPEN;
    }
}
