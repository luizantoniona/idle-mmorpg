import { Component, Input } from "@angular/core";
import { CommonModule } from "@angular/common";

@Component({
    selector: "app-card",
    templateUrl: "./card.component.html",
    styleUrls: ["./card.component.scss"],
    imports: [
        CommonModule
    ],
})

export class CardComponent {
    @Input() onClick?: () => void;
    @Input() clickable = false;

    handleClick(): void {
        if (this.clickable && this.onClick) {
            this.onClick();
        }
    }
}
