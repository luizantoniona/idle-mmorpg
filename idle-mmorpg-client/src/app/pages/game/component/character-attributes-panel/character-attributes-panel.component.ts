import { Component, Input } from '@angular/core';

import { Character } from '../../../../model';

@Component({
    selector: 'app-character-attributes-panel',
    templateUrl: './character-attributes-panel.component.html',
    styleUrl: './character-attributes-panel.component.scss',
    imports: [],
})

export class CharacterAttributesPanel {
    @Input() character!: Character;
}
