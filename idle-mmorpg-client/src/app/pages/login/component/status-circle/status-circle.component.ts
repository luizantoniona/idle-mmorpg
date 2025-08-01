import { Component, Input } from '@angular/core';
import { NgStyle } from '@angular/common';

export type StatusType = 'online' | 'offline' | 'error' | 'loading' | 'unknown';

@Component({
    selector: 'app-status-circle',
    templateUrl: './status-circle.component.html',
    styleUrls: ['./status-circle.component.scss'],
    imports: [NgStyle]
})

export class StatusCircleComponent {
    @Input() status: StatusType = 'unknown';
    @Input() size: number = 32;
}
