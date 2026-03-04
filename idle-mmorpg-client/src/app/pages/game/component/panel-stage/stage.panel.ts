import { Component, Input, inject } from "@angular/core";
import { CommonModule } from "@angular/common";

import { ButtonComponent, LoadingComponent, PanelComponent } from "../../../../component/ui";

import { Character } from "../../../../model";
import { Stage } from "../../../../model";

import { WebsocketService } from "../../../../service";

@Component({
    selector: "app-stage-panel",
    templateUrl: "./stage.panel.html",
    styleUrls: ["./stage.panel.scss"],
    imports: [
        CommonModule,
        ButtonComponent,
        LoadingComponent,
        PanelComponent,
    ],
})

export class StagePanel {
    @Input() character!: Character;
    @Input() stage!: Stage;

    showCombat = false;

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    onNextStage() {
        this.sendMessage({
            type: '',
            payload: '',
        });
    }
}
