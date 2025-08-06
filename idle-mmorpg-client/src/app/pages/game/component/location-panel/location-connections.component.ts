import { Component, Input, Output, inject } from '@angular/core';
import { CommonModule } from '@angular/common';

import { ButtonComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { Location } from '../../../../model';

import { WebsocketService } from '../../../../service/websocket.service';

@Component({
    selector: 'app-location-connections-panel',
    templateUrl: './location-connections.component.html',
    styleUrl: './location-connections.component.scss',
    imports: [
        CommonModule,
        ButtonComponent,
        PanelVerticalComponent,
    ],
})

export class LocationConnectionsComponent {
    @Input() location!: Location;

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    onConnectionClick(locationId: string): void {
        this.sendMessage({
            type: 'character_update_location',
            payload: {
                locationId: locationId,
            },
        });
    }
}
