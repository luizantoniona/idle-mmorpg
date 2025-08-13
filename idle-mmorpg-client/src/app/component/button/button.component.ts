import { Component, EventEmitter, Input, Output } from "@angular/core";

@Component({
    selector: "app-button",
    templateUrl: "./button.component.html",
    styleUrls: ["./button.component.scss"],
    imports: []
})

export class ButtonComponent {
    @Input() text: string = '';
    @Input() disabled: boolean = false;
    @Output() clickEvent = new EventEmitter<void>();

    onClick() {
        if (!this.disabled) {
            this.clickEvent.emit();
        }
    }
}
