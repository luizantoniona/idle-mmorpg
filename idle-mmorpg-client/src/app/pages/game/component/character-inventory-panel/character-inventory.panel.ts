import { Component, Input } from "@angular/core";

import { PanelComponent } from "../../../../component";
import { TooltipComponent } from "../../../../component";

import { Character } from "../../../../model";

@Component({
    selector: "app-character-inventory-panel",
    templateUrl: "./character-inventory.panel.html",
    styleUrls: ["./character-inventory.panel.scss"],
    imports: [
        PanelComponent,
        TooltipComponent
    ],
})

export class CharacterInventoryPanel {
    @Input() character!: Character;
}
