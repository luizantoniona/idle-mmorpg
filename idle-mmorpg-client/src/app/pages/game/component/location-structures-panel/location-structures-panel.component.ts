import { Component, Input, Output, inject } from '@angular/core';
import { CommonModule } from '@angular/common';

import { ButtonComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { Character } from '../../../../model';
import { Location } from '../../../../model';

import { WebsocketService } from '../../../../service/websocket.service';

@Component({
    selector: 'app-location-structures-panel',
    templateUrl: './location-structures-panel.component.html',
    styleUrl: './location-structures-panel.component.scss',
    imports: [
        CommonModule,
        ButtonComponent,
        PanelVerticalComponent,
    ],
})

export class LocationStructuresPanel {
    @Input() location!: Location;
    @Input() character!: Character;

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    onStructureClick(structure: string): void {
        this.sendMessage({
            type: 'character_update_structure',
            payload: {
                structure: structure,
            },
        });
    }
}
