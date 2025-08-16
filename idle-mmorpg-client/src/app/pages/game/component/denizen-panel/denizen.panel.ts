import { Component, Input } from "@angular/core";
import { CommonModule } from "@angular/common";

import { ButtonComponent } from "../../../../component";
import { PanelVerticalComponent } from "../../../../component";
import { PopupComponent } from "../../../../component";

import { QuestPanel } from "./quest-panel/quest.panel";
import { TradePanel } from "./trade-panel/trade.panel";

import { Character, Denizen, Location } from "../../../../model";

@Component({
    selector: "app-denizen-panel",
    templateUrl: "./denizen.panel.html",
    styleUrls: ["./denizen.panel.scss"],
    imports: [
        CommonModule,
        ButtonComponent,
        PanelVerticalComponent,
        PopupComponent,
        QuestPanel,
        TradePanel,
    ],
})

export class DenizenPanel {
    @Input() location!: Location;
    @Input() character!: Character;

    private _selectedDenizen: Denizen | null = null;

    get selectedDenizen(): Denizen | null {
        if (!this._selectedDenizen || !this.location) {
            return this._selectedDenizen;
        }

        return this.location.denizens.find(d => d.id === this._selectedDenizen!.id) ?? null;
    }

    onDenizenClick(denizen: Denizen): void {
        this._selectedDenizen = denizen;
    }

    tradeVisible = false;
    onTradeClick(): void {
        this.tradeVisible = true;
    }

    questVisible = false;
    onQuestsClick(): void {
        this.questVisible = true;
    }
}
