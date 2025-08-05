import { Component, Input, TemplateRef } from '@angular/core';
import { CommonModule, NgTemplateOutlet } from '@angular/common';

@Component({
    selector: 'app-card',
    standalone: true,
    templateUrl: './card.component.html',
    styleUrls: ['./card.component.scss'],
    imports: [
        CommonModule,
        NgTemplateOutlet
    ],
})

export class CardComponent {
    @Input() onClick?: () => void;
    @Input() clickable = false;
    @Input() hoverInfo?: string | TemplateRef<any> | null;

    handleClick(): void {
        if (this.clickable && this.onClick) {
            this.onClick();
        }
    }

    get isHoverable(): boolean {
        return this.clickable || !!this.hoverInfo;
    }

    isTemplateRef(value: any): value is TemplateRef<any> {
        return value instanceof TemplateRef;
    }
}
