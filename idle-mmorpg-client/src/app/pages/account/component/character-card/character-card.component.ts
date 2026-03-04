import { Component, Input } from '@angular/core';
import { CommonModule } from '@angular/common';

import { BarComponent, CardComponent } from '../../../../component/ui';

import type { Character } from '../../../../model';

@Component({
    selector: 'app-character-card',
    templateUrl: './character-card.component.html',
    styleUrls: ['./character-card.component.scss'],
    imports: [
        CommonModule,
        BarComponent,
        CardComponent,
    ]
})
export class CharacterCardComponent {
    @Input() character!: Character;
    @Input() onClick?: () => void;
}
