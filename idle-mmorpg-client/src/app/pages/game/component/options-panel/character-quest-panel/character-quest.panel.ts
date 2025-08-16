import { Component, Input, EventEmitter, Output } from "@angular/core";

import { ButtonComponent } from "../../../../../component";
import { PopupComponent } from "../../../../../component";

import { Character, CharacterQuest } from "../../../../../model";

@Component({
    selector: "app-character-quest-panel",
    templateUrl: "./character-quest.panel.html",
    styleUrls: ["./character-quest.panel.scss"],
    imports: [
        ButtonComponent,
        PopupComponent,
    ],
})

export class CharacterQuestPanel {
    @Input() character!: Character;
    @Input() visible = false;
    @Output() closed = new EventEmitter<void>();

    selectedQuest: CharacterQuest | null = null;

    onSelectedQuest(quest: CharacterQuest) {
        this.selectedQuest = quest;
    }
}
