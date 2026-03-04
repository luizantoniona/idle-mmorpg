import { Component, Input } from "@angular/core";
import { CommonModule } from "@angular/common";

import { BarComponent } from "../../../../component/ui";

import { Character } from "../../../../model";

@Component({
    selector: "app-character-combat-card",
    templateUrl: "./character-combat-card.html",
    styleUrls: ["./character-combat-card.scss"],
    imports: [
        CommonModule,
        BarComponent,
    ],
})

export class CharacterCombatCardComponent {
    @Input() character: Character | null = null;
}
