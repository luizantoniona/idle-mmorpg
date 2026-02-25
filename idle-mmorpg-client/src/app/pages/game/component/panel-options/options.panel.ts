import { Component, Input } from "@angular/core";

import { ButtonComponent, PanelComponent } from "../../../../component/ui";

import { ChatPopup } from "./popup-chat/chat.popup";

import { Character, Stage } from "../../../../model";

@Component({
    selector: "app-options-panel",
    templateUrl: "./options.panel.html",
    styleUrls: ["./options.panel.scss"],
    imports: [
        ButtonComponent,
        PanelComponent,
        ChatPopup,
    ],
})

export class OptionsPanel {
    @Input() character!: Character;
    @Input() stage!: Stage;

    showChat = false;

    onChatClick() {
        this.showChat = true;
    }

    onClose() {
        this.showChat = false;
    }
}
