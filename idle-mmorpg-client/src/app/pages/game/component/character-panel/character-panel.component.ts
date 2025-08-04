import { Component, Input } from '@angular/core';

import { Character } from '../../../../model';

@Component({
    selector: 'app-character-panel',
    templateUrl: './character-panel.component.html',
    styleUrl: './character-panel.component.scss',
    imports: [],
})

export class CharacterPanel {
    @Input() character!: Character;
}
