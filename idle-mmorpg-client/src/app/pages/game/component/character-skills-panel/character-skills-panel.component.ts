import { Component, Input } from '@angular/core';

import { Character } from '../../../../model';

@Component({
    selector: 'app-character-skills-panel',
    templateUrl: './character-skills-panel.component.html',
    styleUrl: './character-skills-panel.component.scss',
    imports: [],
})

export class CharacterSkillsPanel {
    @Input() character!: Character;
}
