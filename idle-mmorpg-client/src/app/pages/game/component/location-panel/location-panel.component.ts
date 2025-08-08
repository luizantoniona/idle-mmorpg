import { Component, Input } from '@angular/core';
import { CommonModule } from '@angular/common';

import { CharacterActionPanel } from '../character-action-panel/character-action-panel.component';
import { LocationActionsPanel } from '../location-actions-panel/location-actions.component'
import { LocationDescriptionPanel } from '../location-description-panel/location-description.component';
import { LocationStructuresPanel } from '../location-structures-panel/location-structures-panel.component';

import { Character } from '../../../../model';
import { Location } from '../../../../model';

@Component({
    selector: 'app-location-panel',
    templateUrl: './location-panel.component.html',
    styleUrl: './location-panel.component.scss',
    imports: [
        CommonModule,
        CharacterActionPanel,
        LocationActionsPanel,
        LocationDescriptionPanel,
        LocationStructuresPanel,
    ],
})

export class LocationPanel {
    @Input() character!: Character;
    @Input() location!: Location;
}
