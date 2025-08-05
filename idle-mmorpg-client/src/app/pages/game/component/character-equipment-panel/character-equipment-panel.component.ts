import { Component, Input } from '@angular/core';

import { PanelVerticalComponent } from '../../../../component';

import { Character } from '../../../../model';

@Component({
    selector: 'app-character-equipment-panel',
    templateUrl: './character-equipment-panel.component.html',
    styleUrl: './character-equipment-panel.component.scss',
    imports: [
        PanelVerticalComponent
    ],
})

export class CharacterEquipmentPanel {
    @Input() character!: Character;
}
