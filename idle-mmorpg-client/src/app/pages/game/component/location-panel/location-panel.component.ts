import { Component, Input } from '@angular/core';
import { CommonModule } from '@angular/common';

import { BarComponent } from '../../../../component';
import { CardComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { Character } from '../../../../model';
import { Location } from '../../../../model';

@Component({
    selector: 'app-location-panel',
    templateUrl: './location-panel.component.html',
    styleUrl: './location-panel.component.scss',
    imports: [
        CommonModule,
        BarComponent,
        CardComponent,
        PanelVerticalComponent,
    ],
})

export class LocationPanel {
    @Input() character!: Character;
    @Input() location!: Location;
}
