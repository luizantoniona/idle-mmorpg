import { Component, Input } from '@angular/core';

import { CardComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { Character } from '../../../../model';

@Component({
    selector: 'app-character-attributes-panel',
    templateUrl: './character-attributes-panel.component.html',
    styleUrl: './character-attributes-panel.component.scss',
    imports: [
        CardComponent,
        PanelVerticalComponent,
    ],
})

export class CharacterAttributesPanel {
    @Input() character!: Character;
}
