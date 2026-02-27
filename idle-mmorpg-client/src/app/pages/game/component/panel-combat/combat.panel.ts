import { Component, Input, Output, EventEmitter, inject } from "@angular/core";
import { CommonModule } from "@angular/common";
import { Subscription } from "rxjs";

import { BarComponent, ButtonComponent, CardComponent, ImageComponent, LoadingComponent, PanelComponent } from "../../../../component/ui";

import { Character, Combat, CombatInstance } from "../../../../model";

import { WebsocketService } from "../../../../service";

@Component({
    selector: "app-combat-panel",
    templateUrl: "./combat.panel.html",
    styleUrls: ["./combat.panel.scss"],
    imports: [
        CommonModule,
        BarComponent,
        ButtonComponent,
        CardComponent,
        ImageComponent,
        LoadingComponent,
        PanelComponent,
    ],
})

export class CombatPanel {
    @Input() character!: Character;
    @Input() combatInstances: CombatInstance[] | null = null;

    private websocketService = inject(WebsocketService);
    private subscriptions = new Subscription();

    combat: Combat | null = null;

    private pendingExit = false;

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
            case 'COMBAT_UPDATE':
                if (!this.pendingExit) {
                    if (data.payload.combat) {
                        this.combat = data.payload.combat
                    }
                }
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
        this.pendingExit = true;
        this.sendMessage({
            type: 'COMBAT_ROOM_EXIT',
            payload: {},
        });

        this.combat = null;
    }
}
