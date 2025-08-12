import { Component, Input } from '@angular/core';

import { ButtonComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { EquipmentSlotComponent } from './equipment-slot.component';

import { Character } from '../../../../model';

@Component({
    selector: 'app-character-equipment-panel',
    templateUrl: './character-equipment.panel.html',
    styleUrl: './character-equipment.panel.scss',
    imports: [
        ButtonComponent,
        PanelVerticalComponent,
        EquipmentSlotComponent,
    ],
})

export class CharacterEquipmentPanel {
    @Input() character!: Character;

    activeTab: 'equipment' | 'tools' = 'equipment';

    setTab(tab: 'equipment' | 'tools') {
        this.activeTab = tab;
    }
}
