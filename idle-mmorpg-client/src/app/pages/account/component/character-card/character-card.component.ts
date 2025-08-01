import { Component, Input } from '@angular/core';
import { NgIf } from '@angular/common';

import { CardComponent } from '../../../../component';

import type { Character } from '../../../../model';

@Component({
    selector: 'app-character-card',
    templateUrl: './character-card.component.html',
    styleUrls: ['./character-card.component.scss'],
    imports: [
        NgIf,
        CardComponent,
    ]
})
export class CharacterCardComponent {
    @Input() character!: Character;
    @Input() onClick?: () => void;
}
