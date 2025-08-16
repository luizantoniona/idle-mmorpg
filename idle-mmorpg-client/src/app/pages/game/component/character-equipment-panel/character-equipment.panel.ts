import { Component, Input } from "@angular/core";

import { ButtonComponent } from "../../../../component";
import { PanelVerticalComponent } from "../../../../component";

import { CharacterEquipPanel } from "./character-equip.panel";
import { EquipmentSlotComponent } from "./equipment-slot.component";

import { Character } from "../../../../model";

@Component({
    selector: "app-character-equipment-panel",
    templateUrl: "./character-equipment.panel.html",
    styleUrls: ["./character-equipment.panel.scss"],
    imports: [
        ButtonComponent,
        PanelVerticalComponent,
        CharacterEquipPanel,
        EquipmentSlotComponent,
    ],
})

export class CharacterEquipmentPanel {
    @Input() character!: Character;

    activeTab: 'equipment' | 'tools' = 'equipment';

    setTab(tab: 'equipment' | 'tools') {
        this.activeTab = tab;
    }

    selectedSlot: string = "";

    showEquip = false;

    onSlotClick(slot: string) {
        this.selectedSlot = slot;
        this.showEquip = true;
    }

    onClose() {
        this.showEquip = false;
    }
}
