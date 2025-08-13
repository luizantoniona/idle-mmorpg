import { Component, Input } from "@angular/core";
import { NgClass } from "@angular/common";

@Component({
    selector: "app-panel",
    templateUrl: "./panel.component.html",
    styleUrls: ["./panel.component.scss"],
    imports: [
        NgClass
    ],
})

export class PanelComponent {
    @Input() className: string = "";
}
