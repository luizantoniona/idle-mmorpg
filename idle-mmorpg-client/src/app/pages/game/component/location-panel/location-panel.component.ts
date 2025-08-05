import { Component, EventEmitter, Input, Output } from '@angular/core';
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

    @Output() actionClick = new EventEmitter<string>();
    @Output() connectionClick = new EventEmitter<string>();

    onActionClick(actionId: string): void {
        this.actionClick.emit(actionId);
    }

    onConnectionClick(destination: string): void {
        this.connectionClick.emit(destination);
    }
}
