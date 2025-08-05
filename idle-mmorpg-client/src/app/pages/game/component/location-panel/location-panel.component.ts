import { Component, Input } from '@angular/core';
import { CommonModule } from '@angular/common';

import { BarComponent } from '../../../../component';
import { ButtonComponent } from '../../../../component';
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
        ButtonComponent,
        PanelVerticalComponent,
    ],
})

export class LocationPanel {
    @Input() character!: Character;
    @Input() location!: Location;

    onActionClick(actionId: string): void {
        console.log('Action clicked:', actionId);
        // TODO: emit to parent or dispatch to backend
    }

    onConnectionClick(connectionId: string): void {
        console.log('Connection clicked:', connectionId);
        // TODO: emit to parent or dispatch to backend
    }
}
