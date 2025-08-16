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

    private _selectedQuestId: string | null = null;

    get selectedQuest(): CharacterQuest | null {
        if (!this._selectedQuestId || !this.character) {
            return null;
        }

        let quest = this.character.quests.proceeding?.find(q => q.id === this._selectedQuestId);

        if (!quest) {
            quest = this.character.quests.finished?.find(q => q.id === this._selectedQuestId);
        }

        return quest ?? null;
    }

    set selectedQuest(quest: CharacterQuest | null) {
        this._selectedQuestId = quest?.id ?? null;
    }

    onSelectedQuest(quest: CharacterQuest) {
        this.selectedQuest = quest;
    }
}
