import { Component, EventEmitter, Input, Output } from "@angular/core";
import { CommonModule } from "@angular/common";

import { ButtonComponent } from "../../../../component";
import { ImageComponent } from "../../../../component/image/image.component";
import { TooltipComponent } from "../../../../component";

import { Item } from "../../../../model";

export type ItemMode = "inventory" | "slot" | "equip";

@Component({
    selector: "app-item",
    templateUrl: "./item.component.html",
    styleUrls: ["./item.component.scss"],
    imports: [
        CommonModule,
        ButtonComponent,
        ImageComponent,
        TooltipComponent,
    ],
})

export class ItemComponent {
    @Input() item!: Item;
    @Input() slot?: string;
    @Input() mode: ItemMode = "inventory";

    @Output() use = new EventEmitter<any>();
    @Output() equip = new EventEmitter<any>();

    onClick() {
        // TODO AJUSTAR ON CLICK
        if (this.mode === "slot") {
            this.equip.emit(this.slot ?? null);

        } else if (this.mode === "inventory") {
            this.use.emit(this.item);

        } else {
            this.equip.emit(this.item ?? null);
        }
    }
}
