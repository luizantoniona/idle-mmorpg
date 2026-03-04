import { Component, Input, Output, EventEmitter, inject } from "@angular/core";
import { CommonModule } from "@angular/common";
import { Subscription } from "rxjs";

import { ButtonComponent, CardComponent, PanelComponent } from "../../../../component/ui";

import { CharacterCombatCardComponent } from "./character-combat-card";
import { CreatureCombatCardComponent } from "./creature-combat-card";

import { Combat, CombatInstance } from "../../../../model";

import { WebsocketService } from "../../../../service";

@Component({
    selector: "app-combat-panel",
    templateUrl: "./combat.panel.html",
    styleUrls: ["./combat.panel.scss"],
    imports: [
        CommonModule,
        ButtonComponent,
        CardComponent,
        PanelComponent,
        CharacterCombatCardComponent,
        CreatureCombatCardComponent
    ],
})

export class CombatPanel {
    private websocketService = inject(WebsocketService);
    private subscriptions = new Subscription();

    combatInstances: CombatInstance[] | null = null;
    combat: Combat | null = null;

    ngOnInit(): void {
        this.subscriptions.add(
            this.websocketService.messages$.subscribe((msg) => this.handleMessage(msg))
        );
    }

    ngOnDestroy(): void {
        this.subscriptions.unsubscribe();
    }

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    handleMessage(data: any): void {
        switch (data.type) {
            case 'COMBAT':
                if (data.payload.combat) {
                    this.combat = data.payload.combat
                }
                break;

            case 'COMBAT_ROOMS':
                this.combatInstances = data.payload.combatInstances;
                break;

            default:
                break;
        }
    }

    onCreateClicked(): void {
        this.sendMessage({
            type: 'COMBAT_ROOM_CREATE',
            payload: {},
        });
    }

    onJoinClicked(id: string): void {
        this.sendMessage({
            type: 'COMBAT_ROOM_ENTER',
            payload: { id: id },
        });
    }

    onExitCombatClicked(): void {
        this.sendMessage({
            type: 'COMBAT_ROOM_EXIT',
            payload: {},
        });

        this.combat = null;
    }
}
