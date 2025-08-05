import { Component, Input } from '@angular/core';

import { PanelHorizontalComponent } from '../../../../component';

@Component({
    selector: 'app-chat-panel',
    templateUrl: './chat-panel.component.html',
    styleUrl: './chat-panel.component.scss',
    imports: [
        PanelHorizontalComponent,
    ],
})

export class ChatPanel {
}
