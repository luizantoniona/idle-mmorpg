import { Component, Input, inject } from "@angular/core";
import { CommonModule } from "@angular/common";

import { PanelComponent } from "../../../../component/ui";

import { SpellComponent } from "../../../../component/game";

import { Character, Spell } from "../../../../model";

import { WebsocketService } from "../../../../service";

@Component({
    selector: "app-character-spells-panel",
    templateUrl: "./character-spells.panel.html",
    styleUrls: ["./character-spells.panel.scss"],
    imports: [
        CommonModule,
        PanelComponent,
        SpellComponent,
    ],
})

export class CharacterSpellsPanel {
    @Input() character!: Character;

    Math = Math;

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    onSpellClicked(spell: Spell): void {
        this.sendMessage({
            type: 'CHARACTER_CAST_SPELL',
            payload: {
                id: spell.id,
                type: spell.type
            },
        });
    }

    onLearnSpellClicked(): void {
        this.sendMessage({
            // TODO: Learn new spell -> open new popup?
        });
    }
}
