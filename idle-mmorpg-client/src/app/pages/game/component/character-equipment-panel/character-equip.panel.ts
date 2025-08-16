import { Component, Input, inject, EventEmitter, Output } from "@angular/core";

import { ButtonComponent } from "../../../../component";
import { PopupComponent } from "../../../../component";

import { TooltipComponent } from "../../../../component";

import { Character } from "../../../../model";
import { Item } from "../../../../model";

import { WebsocketService } from "../../../../service/websocket.service";

@Component({
    selector: "app-character-equip-panel",
    templateUrl: "./character-equip.panel.html",
    styleUrls: ["./character-equip.panel.scss"],
    imports: [
        ButtonComponent,
        PopupComponent,
        TooltipComponent,
    ],
})

export class CharacterEquipPanel {
    @Input() visible = false;
    @Input() character!: Character;
    @Input() slot: string = "";
    @Output() closed = new EventEmitter<void>();

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    getEquipableItems() {
        if (!this.character || !this.character.inventory) {
            return [];
        }

        return this.character.inventory.items.filter(item => {
            if (!["equipament", "weapon", "tools"].includes(item.type)) {
                return false;
            }

            if (item.category === this.slot) {
                return true;
            }

            if (["left-hand", "right-hand"].includes(this.slot) && item.type === "weapon") {
                return true;
            }

            return false;
        });
    }

    equipItem(item: Item) {
        this.sendMessage({
            type: "CHARACTER_EQUIP_ITEM",
            payload: {
                itemId: item.id,
                slot: this.slot
            }
        });
    }
}
