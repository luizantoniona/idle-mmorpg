import { Component, Input, inject, EventEmitter, Output } from "@angular/core";
import { CommonModule } from "@angular/common";

import { ButtonComponent, PopupComponent, TooltipComponent } from "../../../../component/ui";

import { ItemComponent } from "../../../../component/game";

import { Character } from "../../../../model";
import { Item } from "../../../../model";

import { WebsocketService } from "../../../../service";

@Component({
    selector: "app-character-equip-panel",
    templateUrl: "./character-equip.panel.html",
    styleUrls: ["./character-equip.panel.scss"],
    imports: [
        CommonModule,
        ButtonComponent,
        PopupComponent,
        TooltipComponent,
        ItemComponent,
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
            if (!["EQUIPMENT", "WEAPON", "OFFHAND", "TOOL"].includes(item.type)) {
                return false;
            }

            if (item.category === this.slot) {
                return true;
            }

            if (["OFFHAND"].includes(this.slot) && item.type === "OFFHAND") {
                return true;
            }

            if (["WEAPON"].includes(this.slot) && item.type === "WEAPON") {
                return true;
            }

            return false;
        });
    }

    equipItem(item: Item | null) {
        this.sendMessage({
            type: "CHARACTER_ITEM_EQUIP",
            payload: {
                item: item ? item.id : "",
                slot: this.slot
            }
        });

        this.closed.emit();
    }
}
