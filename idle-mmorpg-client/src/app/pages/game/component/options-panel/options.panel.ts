import { Component, Input } from '@angular/core';

import { ButtonComponent } from '../../../../component';
import { PanelHorizontalComponent } from '../../../../component';

import { ChatPanel } from './chat-panel/chat-panel.component';
import { LocationConnectionsPanel } from './location-connections-panel/location-connections-panel.component';

import { Character } from "../../../../model";
import { Location } from "../../../../model";

@Component({
    selector: 'app-options-panel',
    templateUrl: './options.panel.html',
    styleUrl: './options.panel.scss',
    imports: [
        ButtonComponent,
        PanelHorizontalComponent,
        LocationConnectionsPanel,
        ChatPanel
    ],
})

export class OptionsPanel {
    @Input() character!: Character;
    @Input() location!: Location;

    showMap = false;
    showChat = false;

    onMapClick() {
        this.showMap = true;
    }

    onMapClose() {
        this.showMap = false;
    }

    onChatClick() {
        this.showChat = true;
    }

    onChatClose() {
        this.showChat = false;
    }
}
