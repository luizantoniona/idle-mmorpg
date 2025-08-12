import { Component, Input } from '@angular/core';

import { PanelVerticalComponent } from '../../../../component';
import { TooltipComponent } from "../../../../component";

import { Character } from '../../../../model';

@Component({
    selector: 'app-character-inventory-panel',
    templateUrl: './character-inventory-panel.component.html',
    styleUrl: './character-inventory-panel.component.scss',
    imports: [
        PanelVerticalComponent,
        TooltipComponent
    ],
})

export class CharacterInventoryPanel {
    @Input() character!: Character;
}
