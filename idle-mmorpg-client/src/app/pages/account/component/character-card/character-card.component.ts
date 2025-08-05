import { Component, Input } from '@angular/core';
import { CommonModule } from '@angular/common';

import { CardComponent } from '../../../../component';

import type { Character } from '../../../../model';

@Component({
    selector: 'app-character-card',
    templateUrl: './character-card.component.html',
    styleUrls: ['./character-card.component.scss'],
    imports: [
        CommonModule,
        CardComponent,
    ]
})
export class CharacterCardComponent {
    @Input() character!: Character;
    @Input() onClick?: () => void;
}
