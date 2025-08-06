import { Component, Input } from '@angular/core';
import { CommonModule } from '@angular/common';

import { LoadingComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { Location } from '../../../../model';

@Component({
    selector: 'app-location-description-panel',
    templateUrl: './location-description.component.html',
    styleUrl: './location-description.component.scss',
    imports: [
        CommonModule,
        LoadingComponent,
        PanelVerticalComponent,
    ],
})

export class LocationDescriptionPanel {
    @Input() location!: Location;
}
