import { Component, Input } from "@angular/core";
import { CommonModule } from "@angular/common";

import { LoadingComponent } from "../../../../component";
import { PanelComponent } from "../../../../component";

import { Character } from "../../../../model";

@Component({
    selector: "app-character-attributes-panel",
    templateUrl: "./character-attributes-panel.component.html",
    styleUrl: "./character-attributes-panel.component.scss",
    imports: [
        CommonModule,
        LoadingComponent,
        PanelComponent,
    ],
})

export class CharacterAttributesPanel {
    @Input() character!: Character;
}
