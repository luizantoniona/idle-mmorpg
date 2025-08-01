import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { firstValueFrom } from 'rxjs';
import { ServerManager } from '../manager/server.manager';
import { AuthManager } from '../manager/auth.manager';

@Injectable({
    providedIn: 'root',
})
export class APIService {
    private authToken: string | null = null;

    constructor(
        private http: HttpClient,
        private serverManager: ServerManager,
        private authManager: AuthManager
    ) { }

    private getBaseUrl(): string {
        const server = this.serverManager.get();
        if (!server) {
            throw new Error('No server connected.');
        }
        return `http://${server.address}:${server.port}`;
    }

    private getHeaders(): HttpHeaders {
        let headers = new HttpHeaders({
            'Content-Type': 'application/json',
        });

        const token = this.authToken || this.authManager.get()?.sessionID;
        if (token) {
            headers = headers.set('Authorization', `X-Session ${token}`);
        }

        return headers;
    }

    private async request<T>(
        method: 'GET' | 'POST' | 'PUT' | 'DELETE',
        endpoint: string,
        body?: any
    ): Promise<T> {
        const url = `${this.getBaseUrl()}${endpoint}`;
        const options = {
            headers: this.getHeaders(),
            body: method !== 'GET' && body ? body : undefined,
        };

        const response$ = this.http.request<T>(method, url, options);
        return await firstValueFrom(response$);
    }

    getStatus(): Promise<any> {
        return this.request('GET', '/status');
    }

    getData<T>(endpoint: string): Promise<T> {
        return this.request<T>('GET', endpoint);
    }

    postData<T>(endpoint: string, data: any): Promise<T> {
        return this.request<T>('POST', endpoint, data);
    }

    putData<T>(endpoint: string, data: any): Promise<T> {
        return this.request<T>('PUT', endpoint, data);
    }

    deleteData<T>(endpoint: string): Promise<T> {
        return this.request<T>('DELETE', endpoint);
    }

    setAuthToken(token: string): void {
        this.authToken = token;
    }

    clearAuthToken(): void {
        this.authToken = null;
    }
}
