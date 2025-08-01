import { Component, Input } from '@angular/core';
import { PanelComponent } from './panel.component';

@Component({
    selector: 'app-panel-vertical',
    standalone: true,
    imports: [PanelComponent],
    templateUrl: './panel-vertical.component.html',
    styleUrls: ['./panel.component.scss']
})
export class PanelVerticalComponent { }
