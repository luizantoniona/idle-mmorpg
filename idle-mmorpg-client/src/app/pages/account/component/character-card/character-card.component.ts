import { Component, Input } from '@angular/core';
import type { Character } from '../../../../model';
import { NgIf } from '@angular/common';

@Component({
    selector: 'app-character-card',
    templateUrl: './character-card.component.html',
    styleUrls: ['./character-card.component.scss'],
    standalone: true,
    imports: [NgIf]
})
export class CharacterCardComponent {
    @Input() character!: Character;
    @Input() onClick?: () => void;

    handleClick(): void {
        if (this.onClick) this.onClick();
    }
}