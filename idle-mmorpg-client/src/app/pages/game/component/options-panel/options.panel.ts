import { Component, Input } from "@angular/core";

import { ButtonComponent } from "../../../../component";
import { PanelVerticalComponent } from "../../../../component";

import { CharacterQuestPanel } from "./character-quest-panel/character-quest.panel";
import { ChatPanel } from "./chat-panel/chat-panel.component";
import { LocationConnectionsPanel } from "./location-connections-panel/location-connections-panel.component";

import { Character } from "../../../../model";
import { Location } from "../../../../model";

@Component({
    selector: "app-options-panel",
    templateUrl: "./options.panel.html",
    styleUrls: ["./options.panel.scss"],
    imports: [
        ButtonComponent,
        PanelVerticalComponent,
        CharacterQuestPanel,
        ChatPanel,
        LocationConnectionsPanel,
    ],
})

export class OptionsPanel {
    @Input() character!: Character;
    @Input() location!: Location;

    showMap = false;
    showChat = false;
    showQuests = false;

    onMapClick() {
        this.showMap = true;
    }

    onChatClick() {
        this.showChat = true;
    }

    OnQuestsClick() {
        this.showQuests = true;
    }

    onClose() {
        this.showMap = false;
        this.showChat = false;
        this.showQuests = false;
    }
}
