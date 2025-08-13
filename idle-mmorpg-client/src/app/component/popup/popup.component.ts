import { Component, EventEmitter, Input, Output } from "@angular/core";

import { PanelVerticalComponent } from "../panel/panel-vertical.component";

@Component({
    selector: "app-popup",
    templateUrl: "./popup.component.html",
    styleUrls: ["./popup.component.scss"],
    imports: [
        PanelVerticalComponent
    ],
})

export class PopupComponent {
    @Input() visible = false;
    @Output() closed = new EventEmitter<void>();

    close() {
        this.closed.emit();
    }
}
