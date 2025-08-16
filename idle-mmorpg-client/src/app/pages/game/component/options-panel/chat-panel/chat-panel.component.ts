import { Component, Input, EventEmitter, Output, inject } from "@angular/core";

import { PopupComponent } from "../../../../../component";

@Component({
    selector: "app-chat-panel",
    templateUrl: "./chat-panel.component.html",
    styleUrls: ["./chat-panel.component.scss"],
    imports: [
        PopupComponent,
    ],
})

export class ChatPanel {
    @Input() visible = false;
    @Output() closed = new EventEmitter<void>();
}
