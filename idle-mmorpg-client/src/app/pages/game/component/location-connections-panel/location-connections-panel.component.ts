import { Component, Input, Output, inject } from '@angular/core';
import { CommonModule } from '@angular/common';

import { ButtonComponent } from '../../../../component';
import { LoadingComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { Location } from '../../../../model';

import { WebsocketService } from '../../../../service/websocket.service';

@Component({
    selector: 'app-location-connections-panel',
    templateUrl: './location-connections-panel.component.html',
    styleUrl: './location-connections-panel.component.scss',
    imports: [
        CommonModule,
        ButtonComponent,
        LoadingComponent,
        PanelVerticalComponent,
    ],
})

export class LocationConnectionsPanel {
    @Input() location!: Location;

    private websocketService = inject(WebsocketService);

    showPopup = false;

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    onConnectionClick(locationId: string): void {
        this.sendMessage({
            type: 'CHARACTER_LOCATION_UPDATE',
            payload: {
                locationId: locationId,
            },
        });
    }

    onConnectionOpen() {
        this.showPopup = !this.showPopup;
    }
}
