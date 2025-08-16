import { Component, Input, Output, EventEmitter } from "@angular/core";
import { CommonModule } from "@angular/common";

import { TooltipComponent } from "../../../../component";

import { Character, CharacterEquipment } from "../../../../model";

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
    @Input() character!: Character;
    @Input() slot!: keyof CharacterEquipment;
    @Output() slotClick = new EventEmitter<string>();

    onClick() {
        this.slotClick.emit(this.slot);
    }

    get item() {
        if (!this.character || !this.character.equipment) {
            return null;
        }

        return this.character.equipment[this.slot];
    }
}
