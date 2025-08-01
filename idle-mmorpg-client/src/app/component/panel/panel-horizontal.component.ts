import { Component, Input } from '@angular/core';
import { PanelComponent } from './panel.component';

@Component({
    selector: 'app-panel-horizontal',
    standalone: true,
    imports: [PanelComponent],
    templateUrl: './panel-horizontal.component.html',
    styleUrls: ['./panel.component.scss']
})
export class PanelHorizontalComponent { }
