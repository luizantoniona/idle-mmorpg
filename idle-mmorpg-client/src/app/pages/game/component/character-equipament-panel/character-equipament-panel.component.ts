import { Component, Input } from '@angular/core';

import { PanelVerticalComponent } from '../../../../component';

import { Character } from '../../../../model';

@Component({
    selector: 'app-character-equipament-panel',
    templateUrl: './character-equipament-panel.component.html',
    styleUrl: './character-equipament-panel.component.scss',
    imports: [
        PanelVerticalComponent
    ],
})

export class CharacterEquipamentPanel {
    @Input() character!: Character;
}
