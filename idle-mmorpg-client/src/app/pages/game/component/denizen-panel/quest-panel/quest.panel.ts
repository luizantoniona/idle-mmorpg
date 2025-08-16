import { Component, Input, inject, Output, EventEmitter } from "@angular/core";

import { ButtonComponent } from "../../../../../component/button/button.component";

import { Character } from "../../../../../model";
import { Denizen, DenizenQuest } from "../../../../../model";

import { WebsocketService } from "../../../../../service/websocket.service";

@Component({
    selector: "app-quest-panel",
    templateUrl: "./quest.panel.html",
    styleUrls: ["./quest.panel.scss"],
    imports: [
        ButtonComponent,
    ],
})

export class QuestPanel {
    @Input() denizen: Denizen | null = null;
    @Input() character!: Character;
    @Output() close = new EventEmitter<true>();

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    isQuestFinished(questId: string): boolean {
        return this.character.quests.finished && this.character.quests.finished.some(q => q.id === questId);
    }

    acceptQuest(quest: DenizenQuest) {
        this.sendMessage({
            type: "CHARACTER_ACCEPT_DENIZEN_QUEST",
            payload: {
                denizenId: this.denizen?.id,
                questId: quest.id
            }
        });
    }

    finishQuest(quest: DenizenQuest) {
        this.sendMessage({
            type: "CHARACTER_FINISH_DENIZEN_QUEST",
            payload: {
                denizenId: this.denizen?.id,
                questId: quest.id
            }
        });
    }

    onClose() {
        this.close.emit();
    }

    private _selectedQuestId: string | null = null;

    get selectedQuest(): DenizenQuest | null {
        if (!this._selectedQuestId || !this.denizen) {
            return null;
        }

        return this.denizen.quests?.find(q => q.id === this._selectedQuestId) ?? null;
    }

    onSelectedQuest(quest: DenizenQuest) {
        this._selectedQuestId = quest.id;
    }
}
