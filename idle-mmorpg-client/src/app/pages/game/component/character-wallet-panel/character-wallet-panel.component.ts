import { Component, Input } from '@angular/core';

import { PanelVerticalComponent } from '../../../../component';

import { Character } from '../../../../model';

@Component({
    selector: 'app-character-wallet-panel',
    templateUrl: './character-wallet-panel.component.html',
    styleUrl: './character-wallet-panel.component.scss',
    imports: [
        PanelVerticalComponent,
    ],
})

export class CharacterWalletPanel {
    @Input() character!: Character;
}
