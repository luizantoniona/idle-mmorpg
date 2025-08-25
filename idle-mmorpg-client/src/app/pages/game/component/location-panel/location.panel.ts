import { Component, Input, inject } from "@angular/core";
import { CommonModule } from "@angular/common";

import { LoadingComponent } from "../../../../component";
import { PanelVerticalComponent } from "../../../../component";

import { Location } from "../../../../model";

import { WebsocketService } from "../../../../service/websocket.service";

@Component({
    selector: "app-location-panel",
    templateUrl: "./location.panel.html",
    styleUrls: ["./location.panel.scss"],
    imports: [
        CommonModule,
        LoadingComponent,
        PanelVerticalComponent,
    ],
})

export class LocationPanel {
    @Input() location!: Location;

    tiles: { type: 'empty' | 'structure' | 'connection'; content: any }[][] = [];

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    previousConnections: any[] = [];

    ngDoCheck() {
        if (this.location && this.location.connections !== this.previousConnections) {
            this.previousConnections = [...this.location.connections];
            this.generateGrid();
        }
    }

    generateGrid() {
        this.tiles = Array.from({ length: this.location.sizeY }, () =>
            Array.from({ length: this.location.sizeX }, () => ({ type: 'empty', content: null }))
        );

        this.location.structures?.forEach(structure => {
            this.tiles[structure.y][structure.x] = { type: 'structure', content: structure };
        });

        this.location.connections?.forEach(connection => {
            this.tiles[connection.y][connection.x] = { type: 'connection', content: connection };
        });
    }

    onTileClick(tile: any) {
        if (tile.type === 'structure') {
            this.sendMessage({
                type: 'CHARACTER_STRUCTURE_UPDATE',
                payload: {
                    structure: tile.content.id,
                },
            });
        }

        if (tile.type === 'connection') {
            this.sendMessage({
                type: 'CHARACTER_LOCATION_UPDATE',
                payload: {
                    destination: tile.content.destination,
                },
            });
        }
    }
}
