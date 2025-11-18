import { Component, Input, Output, EventEmitter } from "@angular/core";
import { CommonModule } from "@angular/common";

import { ImageComponent } from "../../../../component/image/image.component";
import { TooltipComponent } from "../../../../component";

import { Spell } from "../../../../model";

export type SpellType = "healing" | "attack";

@Component({
    selector: "app-spell",
    templateUrl: "./spell.component.html",
    styleUrls: ["./spell.component.scss"],
    imports: [
        CommonModule,
        ImageComponent,
        TooltipComponent,
    ]
})

export class SpellComponent {
    @Input() spell!: Spell;
    @Input() type: SpellType = "attack";
    @Output() spellClick = new EventEmitter<Spell>();

    Math = Math;

    onClick() {
        this.spellClick.emit(this.spell);
    }
}