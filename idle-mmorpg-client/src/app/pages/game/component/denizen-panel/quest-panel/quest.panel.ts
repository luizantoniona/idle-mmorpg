import { Component, Input, Output, EventEmitter } from "@angular/core";

import { Character } from "../../../../../model";
import { Denizen, DenizenQuest } from "../../../../../model";

@Component({
    selector: "app-quest-panel",
    templateUrl: "./quest.panel.html",
    styleUrls: ["./quest.panel.scss"],
    imports: [],
})

export class QuestPanel {
    @Input() denizen: Denizen | null = null;
    @Input() character!: Character;
    @Output() selectQuest = new EventEmitter<DenizenQuest>();
}
