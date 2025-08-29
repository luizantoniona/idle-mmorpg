import { Component, Input, inject } from "@angular/core";
import { CommonModule } from "@angular/common";

import { ButtonComponent } from "../../../../component";
import { PanelComponent } from "../../../../component";
import { PopupComponent } from "../../../../component";

import { QuestPanel } from "./quest-panel/quest.panel";
import { TradePanel } from "./trade-panel/trade.panel";

import { Character, Denizen, Location } from "../../../../model";

import { WebsocketService } from "../../../../service/websocket.service";

@Component({
    selector: "app-denizen-panel",
    templateUrl: "./denizen.panel.html",
    styleUrls: ["./denizen.panel.scss"],
    imports: [
        CommonModule,
        ButtonComponent,
        PanelComponent,
        PopupComponent,
        QuestPanel,
        TradePanel,
    ],
})

export class DenizenPanel {
    @Input() location!: Location;
    @Input() character!: Character;

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    private _selectedDenizen: Denizen | null = null;

    get selectedDenizen(): Denizen | null {
        if (!this._selectedDenizen || !this.location) {
            return this._selectedDenizen;
        }

        return this.location.denizens.find(d => d.id === this._selectedDenizen!.id) ?? null;
    }

    onDenizenClick(denizen: Denizen): void {
        this._selectedDenizen = denizen;

        this.sendMessage({
            type: "CHARACTER_INTERACT_DENIZEM",
            payload: {
                denizenId: this._selectedDenizen?.id
            }
        });
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
