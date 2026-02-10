import { Component, Input } from "@angular/core";

import { LoadingComponent, PanelComponent } from "../../../../component/ui";

import { Character } from "../../../../model";

@Component({
    selector: "app-character-wallet-panel",
    templateUrl: "./character-wallet-panel.component.html",
    styleUrls: ["./character-wallet-panel.component.scss"],
    imports: [
        LoadingComponent,
        PanelComponent,
    ],
})

export class CharacterWalletPanel {
    @Input() character!: Character;
}
