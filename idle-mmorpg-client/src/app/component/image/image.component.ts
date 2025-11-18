import { Component, Input, OnInit } from '@angular/core';

import { ImageCacheService } from '../../service/image-cache.service';

@Component({
    selector: 'app-image',
    templateUrl: './image.component.html',
    styleUrls: ['./image.component.scss']
})

export class ImageComponent implements OnInit {

    @Input() src!: string;
    @Input() alt = '';
    @Input() width: string | null = null;
    @Input() height: string | null = null;

    loading = true;
    error = false;
    dataUrl: string | null = null;

    constructor(private imageCache: ImageCacheService) { }

    async ngOnInit() {
        if (!this.src) {
            this.error = true;
            return;
        }

        try {
            this.dataUrl = await this.imageCache.loadImage(this.src);

        } catch (e) {
            console.error("Erro ao carregar imagem:", e);
            this.error = true;

        } finally {
            this.loading = false;
        }
    }
}