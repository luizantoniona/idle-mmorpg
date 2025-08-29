import { Component, Input } from "@angular/core";
import { CommonModule } from "@angular/common";

import { BarComponent } from "../../../../component";
import { LoadingComponent } from "../../../../component";
import { PanelComponent } from "../../../../component";

import { Character } from "../../../../model";

@Component({
    selector: "app-character-action-panel",
    templateUrl: "./character-action.panel.html",
    styleUrls: ["./character-action.panel.scss"],
    imports: [
        CommonModule,
        BarComponent,
        LoadingComponent,
        PanelComponent,
    ],
})

export class CharacterActionPanel {
    @Input() character!: Character;

    private startTime = 0;
    private animationId: number | null = null;

    private TICK_MS = 50;

    progress = 0;
    duration = 0;
    actionId = "";

    ngOnChanges() {
        if (!this.character?.action?.id || this.character.action.id === "idle") {
            this.clearAction();
            return;
        }

        this.actionId = this.character.action.id;
        this.duration = this.character.action.duration;

        if (this.character.action.counter === 0) {
            this.startTime = Date.now();

        } else if (this.character.action.counter === this.duration) {
            this.startTime = Date.now() - this.duration * this.TICK_MS;
        }

        this.startProgressLoop();
    }

    private startProgressLoop() {
        if (this.animationId) {
            cancelAnimationFrame(this.animationId);
        }

        const loop = () => {
            const elapsedTicks = (Date.now() - this.startTime) / this.TICK_MS;
            this.progress = Math.min(elapsedTicks, this.duration);
            this.animationId = requestAnimationFrame(loop);
        };

        this.animationId = requestAnimationFrame(loop);
    }

    private clearAction() {
        if (this.animationId) {
            cancelAnimationFrame(this.animationId);
            this.animationId = null;
        }
        this.startTime = 0;
        this.progress = 0;
        this.duration = 0;
        this.actionId = "";
    }
}
