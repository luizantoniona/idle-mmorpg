import { Component, Input, Output, EventEmitter, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Subscription } from 'rxjs';

import { BarComponent } from '../../../../component';
import { ButtonComponent } from '../../../../component';
import { CardComponent } from '../../../../component';
import { LoadingComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { CombatInstance } from '../../../../model';
import { Combat } from '../../../../model';

import { WebsocketService } from '../../../../service/websocket.service';

@Component({
    selector: 'app-combat-panel',
    templateUrl: './combat.panel.html',
    styleUrls: ['./combat.panel.scss'],
    imports: [
        CommonModule,
        BarComponent,
        ButtonComponent,
        CardComponent,
        LoadingComponent,
        PanelVerticalComponent
    ],
})

export class CombatPanel {
    @Output() closeCombat = new EventEmitter<void>();

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
        if (data.type !== 'COMBAT_ROOMS_UPDATE' && data.type !== 'COMBAT_UPDATE' && data.type !== 'CHARACTER_DEAD') {
            return;
        }

        console.log(data)
        switch (data.type) {
            case 'COMBAT_ROOMS_UPDATE':
                this.combatInstances = data.payload.combatInstances
                break;
            case 'COMBAT_UPDATE':
                if (data.payload.combat) {
                    this.combat = data.payload.combat
                }
                break;
            case 'CHARACTER_DEAD':
                this.onExitCombatClicked();
                this.onExitClicked();
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

    onExitClicked(): void {
        this.closeCombat.emit();
    }
}
