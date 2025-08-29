import { Component, Input } from "@angular/core";
import { CommonModule } from "@angular/common";

import { BarComponent } from "../../../../component";
import { LoadingComponent } from "../../../../component";
import { PanelComponent } from "../../../../component";

import { Character } from "../../../../model";

@Component({
    selector: "app-character-action-panel",
    templateUrl: "./character-action.panel.html",
    styleUrls: ["./character-action.panel.scss"],
    imports: [
        CommonModule,
        BarComponent,
        LoadingComponent,
        PanelComponent,
    ],
})

export class CharacterActionPanel {
    @Input() character!: Character;
}
