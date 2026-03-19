import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { firstValueFrom } from 'rxjs';

import { ServerManager, StorageManager } from '../../manager/';

@Injectable({ providedIn: 'root' })
export class ImageCacheService {

    constructor(
        private http: HttpClient,
        private server: ServerManager
    ) { }

    private getBaseUrl(): string {
        const serverData = this.server.get();
        if (!serverData) {
            throw new Error("Server not configured.");
        }

        return serverData.baseUrl;
    }

    async loadImage(path: string): Promise<string> {
        const key = `img-cache:${path}`;

        const cached = StorageManager.get<{ base64: string, timestamp: number }>(key);
        if (cached) {
            return cached.base64;
        }

        const url = `${this.getBaseUrl()}/image/${encodeURIComponent(path)}`;

        let blob: Blob;
        try {
            blob = await firstValueFrom(this.http.get(url, { responseType: 'blob' }));

        } catch (e) {
            console.error("Erro ao carregar imagem:", e);
            throw new Error("Falha ao carregar imagem do servidor.");
        }

        const base64 = await this.blobToBase64(blob);

        StorageManager.set(key, { base64, timestamp: Date.now() });

        return base64;
    }

    private blobToBase64(blob: Blob): Promise<string> {
        return new Promise(resolve => {
            const reader = new FileReader();
            reader.onloadend = () => resolve(reader.result as string);
            reader.readAsDataURL(blob);
        });
    }

    async loadImageBlob(path: string): Promise<Blob> {
        const url = `${this.getBaseUrl()}/image/${encodeURIComponent(path)}`;

        return await firstValueFrom(
            this.http.get(url, { responseType: 'blob' })
        );
    }
}