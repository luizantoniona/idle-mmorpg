import { Component, Input } from '@angular/core';
import { CommonModule } from '@angular/common';

import { BarComponent } from '../../../../component';
import { LoadingComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { Character } from '../../../../model';

@Component({
    selector: 'app-location-character-action-panel',
    templateUrl: './location-character-action.component.html',
    styleUrl: './location-character-action.component.scss',
    imports: [
        CommonModule,
        BarComponent,
        LoadingComponent,
        PanelVerticalComponent,
    ],
})

export class LocationCharacterActionPanel {
    @Input() character!: Character;
}
