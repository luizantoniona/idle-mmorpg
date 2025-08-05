import { Component, Input } from '@angular/core';
import { CommonModule } from '@angular/common';

import { BarComponent } from '../../../../component';
import { LoadingComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { Character } from '../../../../model';

@Component({
    selector: 'app-character-panel',
    templateUrl: './character-panel.component.html',
    styleUrl: './character-panel.component.scss',
    imports: [
        CommonModule,
        BarComponent,
        LoadingComponent,
        PanelVerticalComponent,
    ],
})

export class CharacterPanel {
    @Input() character!: Character;
}
