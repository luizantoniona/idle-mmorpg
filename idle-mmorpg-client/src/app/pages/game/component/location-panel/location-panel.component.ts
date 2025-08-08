import { Component, Input } from '@angular/core';
import { CommonModule } from '@angular/common';

import { LocationActionsPanel } from './location-actions.component'
import { LocationCharacterActionPanel } from './location-character-action.component';
import { LocationDescriptionPanel } from './location-description.component';
import { LocationStructuresPanel } from '../location-structures-panel/location-structures-panel.component';

import { Character } from '../../../../model';
import { Location } from '../../../../model';

@Component({
    selector: 'app-location-panel',
    templateUrl: './location-panel.component.html',
    styleUrl: './location-panel.component.scss',
    imports: [
        CommonModule,
        LocationActionsPanel,
        LocationCharacterActionPanel,
        LocationDescriptionPanel,
        LocationStructuresPanel,
    ],
})

export class LocationPanel {
    @Input() character!: Character;
    @Input() location!: Location;
}
