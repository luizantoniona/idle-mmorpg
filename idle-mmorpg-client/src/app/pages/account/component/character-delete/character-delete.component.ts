import { Component, Input, inject } from "@angular/core";
import { CommonModule } from "@angular/common";
import { FormsModule } from '@angular/forms';
import { Router } from "@angular/router";

import { ButtonComponent } from '../../../../component/button/button.component';
import { PanelVerticalComponent } from '../../../../component/panel/panel-vertical.component';

import { Character } from "../../../../model";

import { APIService } from '../../../../service/api.service';

@Component({
    selector: 'app-character-delete',
    templateUrl: './character-delete.component.html',
    styleUrls: ['./character-delete.component.scss'],
    imports: [
        CommonModule,
        FormsModule,
        PanelVerticalComponent,
        ButtonComponent
    ],
})

export class CharacterDeleteComponent {
    @Input() characters: Character[] = [];

    selectedCharacterId: number | null = null;

    error: string | null = null;

    apiService = inject(APIService);

    async handleDelete() {
        if (!this.selectedCharacterId) {
            return;
        }

        console.log(this.selectedCharacterId)

        try {
            const response = await this.apiService.postData<any>('/remove', {
                characterId: this.selectedCharacterId,
            });

            window.location.reload();

        } catch (err: any) {
            console.error('Deletion failed:', err);
            this.error = err.message || 'Deletion failed.';
        }
    }
}
