import { Component, Input, Output, EventEmitter, inject } from '@angular/core';
import { CommonModule } from '@angular/common';

import { LoadingComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { WebsocketService } from '../../../../service/websocket.service';

@Component({
    selector: 'app-combat-popup',
    templateUrl: './combat-popup.component.html',
    styleUrls: ['./combat-popup.component.scss'],
    imports: [
        CommonModule,
        LoadingComponent,
        PanelVerticalComponent
    ],
})

export class CombatPopupComponent {
    @Input() show = false;
    @Output() close = new EventEmitter<void>();

    private websocketService = inject(WebsocketService);

    onOverlayClick() {
        this.close.emit();
    }

    stopPropagation(event: MouseEvent) {
        event.stopPropagation();
    }
}
