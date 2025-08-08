import { Component, Input, inject } from '@angular/core';
import { CommonModule } from '@angular/common';

import { ButtonComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { CombatPopupComponent } from '../combat-popup/combat-popup.component';

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
        CombatPopupComponent,
    ],
})

export class LocationActionsPanel {
    @Input() location!: Location;

    private websocketService = inject(WebsocketService);

    showCombatPopup = false;

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    onActionClick(action: string): void {
        if (action === 'combat') {
            this.showCombatPopup = true;
        }

        this.sendMessage({
            type: 'CHARACTER_ACTION_UPDATE',
            payload: {
                action: action,
            },
        });
    }

    closePopup(): void {
        this.showCombatPopup = false;
        this.sendMessage({
            type: 'COMBAT_ROOM_EXIT',
            payload: {},
        });

        this.sendMessage({
            type: 'CHARACTER_ACTION_UPDATE',
            payload: {
                action: 'idle',
            },
        });
    }
}
