import { Component, Input, inject } from "@angular/core";
import { CommonModule } from "@angular/common";
import { Subscription } from "rxjs";

import { ButtonComponent } from "../../../../component";
import { PanelVerticalComponent } from "../../../../component";
import { PopupComponent } from "../../../../component";

import { Denizen, Location } from "../../../../model";

import { WebsocketService } from "../../../../service/websocket.service";

@Component({
    selector: "app-denizen-panel",
    templateUrl: "./denizen.panel.html",
    styleUrls: ["./denizen.panel.scss"],
    imports: [
        CommonModule,
        ButtonComponent,
        PanelVerticalComponent,
        PopupComponent,
    ],
})

export class DenizenPanel {
    @Input() location!: Location;

    private websocketService = inject(WebsocketService);
    private subscriptions = new Subscription();

    ngOnInit(): void {
        this.subscriptions.add(
            this.websocketService.messages$.subscribe((msg) => this.handleMessage(msg))
        );
    }

    ngOnDestroy(): void {
        this.subscriptions.unsubscribe();
    }

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    handleMessage(data: any): void {
    }

    selectedDenizen: Denizen | null = null;
    onDenizenClick(denizen: Denizen): void {
        this.selectedDenizen = denizen;
    }

    tradeVisible = false;
    onTradeClick(): void {
        this.tradeVisible = true;
    }

    questVisible = false;
    onQuestsClick(): void {
        this.questVisible = true;
    }

    // this.sendMessage({
    //     type: 'CHARACTER_ACTION_UPDATE',
    //     payload: {
    //         action: action,
    //     },
    // });
}
