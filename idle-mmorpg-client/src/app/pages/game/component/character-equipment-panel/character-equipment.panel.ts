import { Component, Input } from "@angular/core";
import { CommonModule } from "@angular/common";

import { ButtonComponent, PanelComponent } from "../../../../component/ui";

import { ItemComponent } from "../../../../component/game";

import { CharacterEquipPanel } from "./character-equip.panel";

import { Character } from "../../../../model";

@Component({
    selector: "app-character-equipment-panel",
    templateUrl: "./character-equipment.panel.html",
    styleUrls: ["./character-equipment.panel.scss"],
    imports: [
        CommonModule,
        ButtonComponent,
        PanelComponent,
        CharacterEquipPanel,
        ItemComponent,
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
