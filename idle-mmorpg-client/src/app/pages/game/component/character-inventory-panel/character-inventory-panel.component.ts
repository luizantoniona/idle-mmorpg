import { Component, Input } from '@angular/core';

import { Character } from '../../../../model';

@Component({
    selector: 'app-character-inventory-panel',
    templateUrl: './character-inventory-panel.component.html',
    styleUrl: './character-inventory-panel.component.scss',
    imports: [],
})

export class CharacterInventoryPanel {
    @Input() character!: Character;
}
