import { Component, Input } from "@angular/core";
import { CommonModule } from "@angular/common";

import { LoadingComponent } from "../../../../component";
import { PanelVerticalComponent } from "../../../../component";

// import { LocationActionsPanel } from "../location-actions-panel/location-actions.panel";

import { Location } from "../../../../model";

@Component({
    selector: "app-location-panel",
    templateUrl: "./location.panel.html",
    styleUrls: ["./location.panel.scss"],
    imports: [
        CommonModule,
        LoadingComponent,
        PanelVerticalComponent,
        // LocationActionsPanel,
    ],
})

export class LocationPanel {
    @Input() location!: Location;

    tiles: { type: 'empty' | 'structure' | 'connection'; content: any }[][] = [];

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
        if (tile.type === 'structure' || tile.type === 'connection') {
            console.log('Clicked tile:', tile.content);
        }
    }
}
