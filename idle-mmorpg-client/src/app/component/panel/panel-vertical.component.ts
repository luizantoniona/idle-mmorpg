import { Component } from "@angular/core";

import { PanelComponent } from "./panel.component";

@Component({
    selector: "app-panel-vertical",
    templateUrl: "./panel-vertical.component.html",
    styleUrls: ["./panel.component.scss"],
    imports: [
        PanelComponent
    ],
})

export class PanelVerticalComponent { }
