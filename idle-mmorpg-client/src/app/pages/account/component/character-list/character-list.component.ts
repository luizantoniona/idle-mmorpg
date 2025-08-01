import { Component, Input, Output, EventEmitter } from '@angular/core';
import type { Character } from '../../../../model';
import { CharacterCardComponent } from '../character-card/character-card.component';
import { NgFor } from '@angular/common';

@Component({
    selector: 'app-character-list',
    templateUrl: './character-list.component.html',
    imports: [NgFor, CharacterCardComponent],
})
export class CharacterListComponent {
    @Input() characters: Character[] = [];
    @Output() onSelect = new EventEmitter<Character>();

    selectCharacter(character: Character) {
        this.onSelect.emit(character);
    }
}