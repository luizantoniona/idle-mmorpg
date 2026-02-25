import { Component, Input, EventEmitter, Output, inject } from "@angular/core";

import { PopupComponent } from "../../../../../component/ui";

@Component({
    selector: "app-chat-popup",
    templateUrl: "./chat.popup.html",
    styleUrls: ["./chat.popup.scss"],
    imports: [
        PopupComponent,
    ],
})

export class ChatPopup {
    @Input() visible = false;
    @Output() closed = new EventEmitter<void>();
}
