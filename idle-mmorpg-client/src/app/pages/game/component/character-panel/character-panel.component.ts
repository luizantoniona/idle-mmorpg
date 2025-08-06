import { Component, Input, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Router } from '@angular/router';

import { BarComponent } from '../../../../component';
import { ButtonComponent } from '../../../../component';
import { LoadingComponent } from '../../../../component';
import { PanelVerticalComponent } from '../../../../component';

import { Character } from '../../../../model';

@Component({
    selector: 'app-character-panel',
    templateUrl: './character-panel.component.html',
    styleUrl: './character-panel.component.scss',
    imports: [
        CommonModule,
        BarComponent,
        ButtonComponent,
        LoadingComponent,
        PanelVerticalComponent,
    ],
})

export class CharacterPanel {
    @Input() character!: Character;

    private router = inject(Router);

    handleClick() {
        this.router.navigate(['/account']);
    }

    get nameLevel(): string {
        return this.character?.progression
            ? `${this.character.name} (${this.character.progression.level})`
            : this.character?.name || '...';
    }
}
