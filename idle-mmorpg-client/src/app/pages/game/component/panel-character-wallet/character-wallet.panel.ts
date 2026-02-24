import { Component, Input } from "@angular/core";
import { CommonModule } from "@angular/common";

import { LoadingComponent, PanelComponent } from "../../../../component/ui";

import { Character } from "../../../../model";

@Component({
    selector: "app-character-wallet-panel",
    templateUrl: "./character-wallet.panel.html",
    styleUrls: ["./character-wallet.panel.scss"],
    imports: [
        CommonModule,
        LoadingComponent,
        PanelComponent,
    ],
})

export class CharacterWalletPanel {
    @Input() character!: Character;
}
