import { Component, Input, inject } from "@angular/core";
import { CommonModule } from "@angular/common";

import { CombatPanel } from "../combat-panel/combat.panel";

import { Character } from "../../../../model";
import { Stage } from "../../../../model";

import { WebsocketService } from "../../../../service";

@Component({
    selector: "app-main-panel",
    templateUrl: "./main.panel.html",
    styleUrls: ["./main.panel.scss"],
    imports: [
        CommonModule,
        CombatPanel,
    ],
})

export class MainPanel {
    @Input() character!: Character;
    @Input() stage!: Stage;

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
