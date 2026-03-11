import { Component, Input, inject } from "@angular/core";
import { CommonModule } from "@angular/common";

import { BarComponent, ButtonComponent, LoadingComponent, PanelComponent } from "../../../../component/ui";

import { Character } from "../../../../model";
import { Action, ActionOption } from "../../../../model/action/action.model";

import { WebsocketService } from "../../../../service";

@Component({
    selector: "app-character-action-panel",
    templateUrl: "./character-action.panel.html",
    styleUrls: ["./character-action.panel.scss"],
    imports: [
        CommonModule,
        BarComponent,
        ButtonComponent,
        LoadingComponent,
        PanelComponent,
    ],
})

export class CharacterActionPanel {
    @Input() character!: Character;

    selectedActionType: number | null = null;
    selectedOptions: ActionOption[] = [];

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    onActionClicked(action: Action): void {

        if (!action.options || action.options.length === 0) {
            return;
        }

        if (action.options.length > 1) {
            this.selectedActionType = action.type;
            this.selectedOptions = action.options;
            return;
        }

        const option = action.options[0];
        this.sendMessage({
            type: 'CHARACTER_ACTION_SET',
            payload: {
                type: action.type,
                optionStage: option.stage
            },
        });
    }

    onOptionClicked(option: ActionOption): void {
        if (this.selectedActionType === null) {
            return;
        }

        this.sendMessage({
            type: 'CHARACTER_ACTION_SET',
            payload: {
                type: this.selectedActionType,
                optionStage: option.stage
            },
        });

        this.selectedActionType = null;
        this.selectedOptions = [];
    }
}
