import { Component, Input } from "@angular/core";
import { CommonModule } from "@angular/common";

import { BarComponent, ImageComponent } from "../../../../component/ui";

import { Creature } from "../../../../model";

@Component({
    selector: "app-creature-combat-card",
    templateUrl: "./creature-combat-card.html",
    styleUrls: ["./creature-combat-card.scss"],
    imports: [
        CommonModule,
        BarComponent,
        ImageComponent
    ],
})

export class CreatureCombatCardComponent {
    @Input() creature: Creature | null = null;
}
