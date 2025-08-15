import { Component, Input, EventEmitter, Output, inject } from "@angular/core";

import { PopupComponent } from "../../../../../component";
import { Character } from "../../../../../model";

@Component({
    selector: "app-character-quest-panel",
    templateUrl: "./character-quest.panel.html",
    styleUrls: ["./character-quest.panel.scss"],
    imports: [
        PopupComponent,
    ],
})

export class CharacterQuestPanel {
    @Input() character!: Character;
    @Input() visible = false;
    @Output() closed = new EventEmitter<void>();
}
