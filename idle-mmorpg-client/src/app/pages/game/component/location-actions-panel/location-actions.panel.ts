import { Component, EventEmitter, Input, inject, Output } from "@angular/core";
import { CommonModule } from "@angular/common";

import { ButtonComponent } from "../../../../component";
import { PanelVerticalComponent } from "../../../../component";

import { Character, Location } from "../../../../model";

import { WebsocketService } from "../../../../service/websocket.service";

@Component({
    selector: "app-location-actions-panel",
    templateUrl: "./location-actions.panel.html",
    styleUrls: ["./location-actions.panel.scss"],
    imports: [
        CommonModule,
        ButtonComponent,
        PanelVerticalComponent,
    ],
})

export class LocationActionsPanel {
    @Input() location!: Location;
    @Input() character!: Character;
    @Output() openCombat = new EventEmitter<void>();

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    onActionClick(action: string): void {
        if (action === 'combat') {
            this.openCombat.emit();
        }

        this.sendMessage({
            type: 'CHARACTER_ACTION_UPDATE',
            payload: {
                action: action,
            },
        });
    }
}
