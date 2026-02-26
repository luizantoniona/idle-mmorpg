import { Component, signal, OnInit } from "@angular/core";
import { RouterOutlet } from "@angular/router";

import { ImageCacheService } from "./service";

@Component({
    selector: "app-root",
    templateUrl: "./app.html",
    styleUrl: "./app.scss",
    imports: [
        RouterOutlet
    ],
})
export class App implements OnInit {
    protected readonly title = signal("iMMO");

    constructor(private imageCache: ImageCacheService) { }

    async ngOnInit() {
        await this.setFavicon('logo.png');
    }

    private async setFavicon(path: string) {
        try {
            const blob = await this.imageCache.loadImageBlob(path);

            const links = document.querySelectorAll("link[rel*='icon']");
            links.forEach(l => l.remove());

            const link = document.createElement("link");
            link.rel = "icon";
            link.type = "image/png";

            const blobUrl = URL.createObjectURL(blob);
            link.href = blobUrl;

            document.head.appendChild(link);

        } catch (e) {
            console.error("Erro ao carregar favicon:", e);
        }
    }
}
