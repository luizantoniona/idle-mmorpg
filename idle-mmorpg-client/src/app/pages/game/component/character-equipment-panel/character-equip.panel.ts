import { Component, Input, inject, EventEmitter, Output } from "@angular/core";
import { CommonModule } from "@angular/common";

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
        CommonModule,
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

    getSlotName(): string {
        if (!this.slot) return "";

        const treated = this.slot
            .replace(/([a-z])([A-Z])/g, "$1 $2");

        return treated
            .split(" ")
            .map(word => word.charAt(0).toUpperCase() + word.slice(1))
            .join(" ");
    }

    getEquipableItems() {
        if (!this.character || !this.character.inventory) {
            return [];
        }

        return this.character.inventory.items.filter(item => {
            if (!["equipment", "weapon", "tool"].includes(item.type)) {
                return false;
            }

            if (item.category === this.slot) {
                return true;
            }

            if (["leftHand", "rightHand"].includes(this.slot) && item.type === "weapon") {
                return true;
            }

            return false;
        });
    }

    equipItem(item: Item | null) {
        this.sendMessage({
            type: "CHARACTER_EQUIP_ITEM",
            payload: {
                itemId: item ? item.id : "",
                slot: this.slot
            }
        });

        this.closed.emit();
    }
}
