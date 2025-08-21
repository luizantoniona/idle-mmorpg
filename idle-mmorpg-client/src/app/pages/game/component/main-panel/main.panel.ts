import { Component, Input, inject } from "@angular/core";
import { CommonModule } from "@angular/common";

import { CharacterActionPanel } from "../character-action-panel/character-action.panel";
import { CharacterSpellsPanel } from "../character-spells-panel/character-spells.panel";
import { CombatPanel } from "../combat-panel/combat.panel";
import { DenizenPanel } from "../denizen-panel/denizen.panel";
import { LocationPanel } from "../location-panel/location.panel";
import { LocationActionsPanel } from "../location-actions-panel/location-actions.panel";
import { LocationStructuresPanel } from "../location-structures-panel/location-structures-panel.component";

import { Character } from "../../../../model";
import { Location } from "../../../../model";

import { WebsocketService } from "../../../../service/websocket.service";

@Component({
    selector: "app-main-panel",
    templateUrl: "./main.panel.html",
    styleUrls: ["./main.panel.scss"],
    imports: [
        CommonModule,
        CharacterActionPanel,
        CombatPanel,
        DenizenPanel,
        LocationPanel,
        LocationActionsPanel,
        LocationStructuresPanel,
        CharacterSpellsPanel,
    ],
})

export class MainPanel {
    @Input() character!: Character;
    @Input() location!: Location;

    showCombat = false;

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    onOpenCombat(): void {
        this.showCombat = true;
    }

    onCloseCombat(): void {
        this.sendMessage({
            type: 'CHARACTER_ACTION_UPDATE',
            payload: {
                action: 'idle',
            },
        });

        this.showCombat = false;
    }
}
