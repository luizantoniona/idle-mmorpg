import { Component, Input, inject } from "@angular/core";
import { CommonModule } from "@angular/common";

import { ButtonComponent } from '../../../../component';
import { LoadingComponent } from "../../../../component";
import { PanelComponent } from "../../../../component";

import { LocationRendererPanel } from "./location-renderer.panel";

import { Character, Location } from "../../../../model";

import { WebsocketService } from "../../../../service/websocket.service";

@Component({
    selector: "app-location-panel",
    templateUrl: "./location.panel.html",
    styleUrls: ["./location.panel.scss"],
    imports: [
        CommonModule,
        ButtonComponent,
        LoadingComponent,
        PanelComponent,
        LocationRendererPanel
    ],
})

export class LocationPanel {
    @Input() location!: Location;
    @Input() character!: Character;

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    onLeaveStructureClicked(structure: string): void {
        this.sendMessage({
            type: 'CHARACTER_STRUCTURE_UPDATE',
            payload: {
                structure: structure,
            },
        });
    }

    getStructure(structureId?: string) {
        return this.location?.structures?.find(structure => structure.id === structureId) || null;
    }
}
