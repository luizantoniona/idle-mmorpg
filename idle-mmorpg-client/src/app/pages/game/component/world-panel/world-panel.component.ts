import { Component, Input } from '@angular/core';

import { Character } from '../../../../model';

@Component({
    selector: 'app-world-panel',
    templateUrl: './world-panel.component.html',
    styleUrl: './world-panel.component.scss',
    imports: [],
})

export class WorldPanel {
    @Input() character!: Character;
}
