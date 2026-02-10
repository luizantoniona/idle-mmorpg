import { Component, EventEmitter, Input, Output } from "@angular/core";

import { PanelComponent } from "../panel/panel.component";

@Component({
    selector: "app-popup",
    templateUrl: "./popup.component.html",
    styleUrls: ["./popup.component.scss"],
    imports: [
        PanelComponent
    ],
})

export class PopupComponent {
    @Input() visible = false;
    @Output() closed = new EventEmitter<void>();

    close() {
        this.closed.emit();
    }
}
