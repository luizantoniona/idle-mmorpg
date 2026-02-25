import { Component, Input, inject } from "@angular/core";
import { CommonModule } from "@angular/common";

import { ButtonComponent, PanelComponent } from "../../../../component/ui";

import { CombatPanel } from "../panel-combat/combat.panel";

import { Character } from "../../../../model";
import { Stage } from "../../../../model";

import { WebsocketService } from "../../../../service";

@Component({
    selector: "app-stage-panel",
    templateUrl: "./stage.panel.html",
    styleUrls: ["./stage.panel.scss"],
    imports: [
        CommonModule,
        ButtonComponent,
        PanelComponent,
        CombatPanel,
    ],
})

export class StagePanel {
    @Input() character!: Character;
    @Input() stage!: Stage;

    showCombat = false;

    private websocketService = inject(WebsocketService);

    onNextStage() { }

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
