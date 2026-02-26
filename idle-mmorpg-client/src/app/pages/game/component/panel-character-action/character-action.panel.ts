import { Component, Input, inject } from "@angular/core";
import { CommonModule } from "@angular/common";

import { BarComponent, ButtonComponent, LoadingComponent, PanelComponent } from "../../../../component/ui";

import { Character } from "../../../../model";

import { WebsocketService } from "../../../../service";

@Component({
    selector: "app-character-action-panel",
    templateUrl: "./character-action.panel.html",
    styleUrls: ["./character-action.panel.scss"],
    imports: [
        CommonModule,
        BarComponent,
        ButtonComponent,
        LoadingComponent,
        PanelComponent,
    ],
})

export class CharacterActionPanel {
    @Input() character!: Character;

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    onActionClicked(type: number): void {

        // TODO: If Action has options, it should open a new tab/popup with the options before sending the message

        this.sendMessage({
            type: 'CHARACTER_SET_ACTION',
            payload: {
                type: type,
            },
        });
    }
}
