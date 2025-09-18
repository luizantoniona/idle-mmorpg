import { Component, EventEmitter, Input, Output } from "@angular/core";
import { CommonModule } from "@angular/common";

import { ButtonComponent } from "../../../../component";
import { TooltipComponent } from "../../../../component";

import { Item } from "../../../../model";

export type ItemMode = "inventory" | "slot";

@Component({
    selector: "app-item",
    templateUrl: "./item.component.html",
    styleUrls: ["./item.component.scss"],
    imports: [
        CommonModule,
        ButtonComponent,
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
        if (this.mode === "slot") {
            this.equip.emit(this.slot ?? null);
        }
    }
}
