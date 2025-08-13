import { Component, Input } from "@angular/core";

@Component({
    selector: "app-bar",
    templateUrl: "./bar.component.html",
    styleUrls: ["./bar.component.scss"],
    imports: [],
})

export class BarComponent {
    @Input() label: string = "";
    @Input() value: number = 0;
    @Input() max: number = 100;
    @Input() color: string = "#4caf50";

    get percentage(): number {
        return Math.min((this.value / this.max) * 100, 100);
    }

    get tooltip(): string {
        return `${this.label}: ${this.value} / ${this.max}`;
    }
}
