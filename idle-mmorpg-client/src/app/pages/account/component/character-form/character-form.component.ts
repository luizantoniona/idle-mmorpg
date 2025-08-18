import { Component, inject } from "@angular/core";
import { CommonModule } from "@angular/common";
import { FormBuilder, ReactiveFormsModule, Validators } from "@angular/forms";
import { Router } from "@angular/router";

import { ButtonComponent } from "../../../../component";
import { PanelVerticalComponent } from "../../../../component";
import { InputFieldComponent } from "../../../../component";

import { APIService } from "../../../../service/api.service";

@Component({
    selector: "app-character-form",
    templateUrl: "./character-form.component.html",
    styleUrls: ["./character-form.component.scss"],
    imports: [
        CommonModule,
        ReactiveFormsModule,
        PanelVerticalComponent,
        InputFieldComponent,
        ButtonComponent
    ],
})

export class CharacterFormComponent {
    fb = inject(FormBuilder);
    router = inject(Router);
    form = this.fb.group({
        name: ['', Validators.required],
    });
    error: string | null = null;

    apiService = inject(APIService);

    async handleSubmit() {
        if (this.form.invalid) return;
        this.error = null;

        const { name } = this.form.value;

        try {
            const loginResponse = await this.apiService.postData<any>('/create', { name });

            if (!loginResponse?.idCharacter) {
                throw new Error('Character creation failed');
            }

            window.location.reload();

        } catch (err: any) {
            console.error('Creation failed:', err);
            this.error = err.message || 'Creation failed.';
        }
    }
}
