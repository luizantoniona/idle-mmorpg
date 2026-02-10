import { Component, Input } from "@angular/core";

import { ButtonComponent, PanelComponent } from "../../../../component/ui";

import { ChatPanel } from "./chat-panel/chat-panel.component";

import { Character } from "../../../../model";
import { Stage } from "../../../../model";

@Component({
    selector: "app-options-panel",
    templateUrl: "./options.panel.html",
    styleUrls: ["./options.panel.scss"],
    imports: [
        ButtonComponent,
        PanelComponent,
        ChatPanel,
    ],
})

export class OptionsPanel {
    @Input() character!: Character;
    @Input() location!: Location;

    showChat = false;
    showQuests = false;

    onChatClick() {
        this.showChat = true;
    }

    OnQuestsClick() {
        this.showQuests = true;
    }

    onClose() {
        this.showChat = false;
        this.showQuests = false;
    }
}
