import { Component, Input, inject } from "@angular/core";
import { CommonModule } from "@angular/common";

import { PanelComponent } from "../../../../component";

import { ItemComponent } from "../item/item.component";

import { Character } from "../../../../model";
import { Item } from "../../../../model";

import { WebsocketService } from "../../../../service/websocket.service";

@Component({
    selector: "app-character-inventory-panel",
    templateUrl: "./character-inventory.panel.html",
    styleUrls: ["./character-inventory.panel.scss"],
    imports: [
        CommonModule,
        PanelComponent,
        ItemComponent,
    ],
})

export class CharacterInventoryPanel {
    @Input() character!: Character;

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    useItem(item: Item | null) {
        this.sendMessage({
            type: "CHARACTER_USE_ITEM",
            payload: {
                itemId: item ? item.id : ""
            }
        });
    }
}
