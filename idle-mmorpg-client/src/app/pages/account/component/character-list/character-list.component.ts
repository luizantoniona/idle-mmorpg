import { Component, Input, Output, EventEmitter } from '@angular/core';
import { NgFor } from '@angular/common';

import { CharacterCardComponent } from '../character-card/character-card.component';
import { PanelHorizontalComponent } from '../../../../component/panel/panel-horizontal.component';

import type { Character } from '../../../../model';

@Component({
    selector: 'app-character-list',
    templateUrl: './character-list.component.html',
    imports: [
        NgFor,
        CharacterCardComponent,
        PanelHorizontalComponent
    ],
})
export class CharacterListComponent {
    @Input() characters: Character[] = [];
    @Output() onSelect = new EventEmitter<Character>();

    selectCharacter(character: Character) {
        this.onSelect.emit(character);
    }
}
