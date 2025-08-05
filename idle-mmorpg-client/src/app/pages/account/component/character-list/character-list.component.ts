import { Component, Input, Output, EventEmitter } from '@angular/core';
import { CommonModule } from '@angular/common';

import { CharacterCardComponent } from '../character-card/character-card.component';
import { PanelHorizontalComponent } from '../../../../component/panel/panel-horizontal.component';

import type { Character } from '../../../../model';

@Component({
    selector: 'app-character-list',
    templateUrl: './character-list.component.html',
    imports: [
        CommonModule,
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
