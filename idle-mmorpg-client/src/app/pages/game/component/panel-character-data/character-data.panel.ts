import { Component, Input, inject } from "@angular/core";
import { CommonModule } from "@angular/common";
import { Router } from "@angular/router";

import { BarComponent, ButtonComponent, LoadingComponent, PanelComponent } from "../../../../component/ui";

import { Character } from "../../../../model";

@Component({
    selector: "app-character-data-panel",
    templateUrl: "./character-data.panel.html",
    styleUrls: ["./character-data.panel.scss"],
    imports: [
        CommonModule,
        BarComponent,
        ButtonComponent,
        LoadingComponent,
        PanelComponent,
    ],
})

export class CharacterDataPanel {
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
