import { ServerManager } from "../manager/ServerManager";
import { AuthManager } from "../manager/AuthManager";

export class APIService {
    static authToken: string | null = null;

    private static getBaseUrl(): string {
        const server = ServerManager.get();
        if (!server) {
            throw new Error("No server connected.");
        }

        return `http://${server.address}:${server.port}`;
    }

    private static getHeaders(): HeadersInit {
        const headers: HeadersInit = {
            "Content-Type": "application/json",
        };

        const token = this.authToken || AuthManager.get()?.sessionID;
        if (token) {
            headers["Authorization"] = `X-Session ${token}`;
        }

        return headers;
    }

    private static async request<T>(
        method: 'GET' | 'POST' | 'PUT' | 'DELETE',
        endpoint: string,
        body?: any
    ): Promise<T> {
        const url = `${this.getBaseUrl()}${endpoint}`;
        const options: RequestInit = {
            method,
            headers: this.getHeaders(),
        };

        if (method !== 'GET' && body) {
            options.body = JSON.stringify(body);
        }

        const response = await fetch(url, options);

        if (!response.ok) {
            const message = await response.text();
            throw new Error(`API Error ${response.status}: ${message}`);
        }

        return await response.json();
    }

    static getStatus(): Promise<any> {
        return this.request('GET', '/status');
    }

    static getData<T>(endpoint: string): Promise<T> {
        return this.request<T>('GET', endpoint);
    }

    static postData<T>(endpoint: string, data: any): Promise<T> {
        return this.request<T>('POST', endpoint, data);
    }

    static putData<T>(endpoint: string, data: any): Promise<T> {
        return this.request<T>('PUT', endpoint, data);
    }

    static deleteData<T>(endpoint: string): Promise<T> {
        return this.request<T>('DELETE', endpoint);
    }

    static setAuthToken(token: string) {
        this.authToken = token;
    }

    static clearAuthToken() {
        this.authToken = null;
    }
}
