import { Component, Input, Output, EventEmitter, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Subscription } from 'rxjs';

import { ButtonComponent } from '../../../../component';
import { CardComponent } from '../../../../component';
import { LoadingComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { CombatInstance } from '../../../../model';
import { Combat } from '../../../../model';

import { WebsocketService } from '../../../../service/websocket.service';

@Component({
    selector: 'app-combat-popup',
    templateUrl: './combat-popup.component.html',
    styleUrls: ['./combat-popup.component.scss'],
    imports: [
        CommonModule,
        ButtonComponent,
        CardComponent,
        LoadingComponent,
        PanelVerticalComponent
    ],
})

export class CombatPopupComponent {
    @Output() close = new EventEmitter<void>();

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
        console.log(data)
        switch (data.type) {
            case 'COMBAT_ROOMS_UPDATE':
                if (data.payload.combatInstances) {
                    this.combatInstances = data.payload.combatInstances
                }
                break;
            case 'COMBAT_UPDATE':
                if (data.payload.combat) {
                    this.combat = data.payload.combat
                }
                break;
        }
    }

    onCreateClicked(): void {
        this.sendMessage({
            type: 'COMBAT_ROOM_CREATE',
            payload: {},
        });
    }

    onJoinClicked(id: number): void {
        this.sendMessage({
            type: 'COMBAT_ROOM_ENTER',
            payload: { id: id },
        });
    }

    onExitClicked(): void {
        this.sendMessage({
            type: 'COMBAT_ROOM_EXIT',
            payload: {},
        });

        this.combat = null;
    }

    onOverlayClick() {
        this.close.emit();
    }

    stopPropagation(event: MouseEvent) {
        event.stopPropagation();
    }
}
