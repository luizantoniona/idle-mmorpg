import { Component, Input } from '@angular/core';

import { Character } from '../../../../model';

@Component({
    selector: 'app-character-wallet-panel',
    templateUrl: './character-wallet-panel.component.html',
    styleUrl: './character-wallet-panel.component.scss',
    imports: [],
})

export class CharacterWalletPanel {
    @Input() character!: Character;
}
