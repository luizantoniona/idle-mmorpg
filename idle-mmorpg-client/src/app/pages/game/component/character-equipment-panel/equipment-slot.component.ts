import { Component, Input, Output, EventEmitter } from "@angular/core";
import { CommonModule } from "@angular/common";

import { TooltipComponent } from "../../../../component";

import { Item } from "../../../../model";

@Component({
    selector: "app-equipment-slot",
    templateUrl: "./equipment-slot.component.html",
    styleUrls: ["./equipment-slot.component.scss"],
    imports: [
        CommonModule,
        TooltipComponent
    ],
})

export class EquipmentSlotComponent {
    @Input() item: Item | null = null;
    @Input() slot: string = "";
    @Output() slotClick = new EventEmitter<string>();

    onClick() {
        this.slotClick.emit(this.slot);
    }
}
