import { Component, Input, Output, inject } from '@angular/core';
import { CommonModule } from '@angular/common';

import { ButtonComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { Location } from '../../../../model';

import { WebsocketService } from '../../../../service/websocket.service';

@Component({
    selector: 'app-location-actions-panel',
    templateUrl: './location-actions.component.html',
    styleUrl: './location-actions.component.scss',
    imports: [
        CommonModule,
        ButtonComponent,
        PanelVerticalComponent,
    ],
})

export class LocationActionsPanel {
    @Input() location!: Location;

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    onActionClick(action: string): void {
        this.sendMessage({
            type: 'character_update_action',
            payload: {
                action: action,
            },
        });
    }
}
