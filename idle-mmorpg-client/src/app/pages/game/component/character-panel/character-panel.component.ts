import { Component, Input } from '@angular/core';

import { BarComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { Character } from '../../../../model';

@Component({
    selector: 'app-character-panel',
    templateUrl: './character-panel.component.html',
    styleUrl: './character-panel.component.scss',
    imports: [
        BarComponent,
        PanelVerticalComponent,
    ],
})

export class CharacterPanel {
    @Input() character!: Character;
}
