import { Component, OnInit, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Router } from '@angular/router';

import { ButtonComponent } from '../../component';
import { LoadingComponent } from '../../component';
import { PanelVerticalComponent } from '../../component';

import { CharacterFormComponent } from './component/character-form/character-form.component';
import { CharacterListComponent } from './component/character-list/character-list.component';

import { APIService } from '../../service/api.service';
import { AuthService } from '../../service/auth.service';
import type { Character } from '../../model';

@Component({
    selector: 'app-account-page',
    standalone: true,
    imports: [
        CommonModule,
        ButtonComponent,
        LoadingComponent,
        PanelVerticalComponent,
        CharacterFormComponent,
        CharacterListComponent,
    ],
    templateUrl: './account.page.html',
    styleUrls: ['./account.page.scss'],
})

export class AccountPage implements OnInit {
    private router = inject(Router);
    private apiService = inject(APIService);
    private authService = inject(AuthService);

    characters: Character[] = [];
    loading = true;
    error: string | null = null;

    async ngOnInit(): Promise<void> {
        this.loading = true;

        try {
            const res = await this.apiService.getData<{ characters: Character[] }>('/characters');
            this.characters = res.characters ?? [];
            this.error = null;

        } catch (err: any) {
            console.error('Failed to fetch characters:', err);
            this.error = err?.message || 'Unknown error';

        } finally {
            this.loading = false;
        }
    }

    async logout(): Promise<void> {
        try {
            const logoutResponse = await this.apiService.postNoData<any>('/logout');

            this.authService.logout();
            this.router.navigate(['/']);

        } catch (err: any) {
            console.error('Logout failed:', err);
            this.error = err.message || 'Logout failed.';
        }
    }

    getUsername(): string | null {
        return this.authService.getUsername();
    }

    getSessionId(): string | null {
        return this.authService.getSessionId();
    }

    handleStartGame(character: Character): void {
        localStorage.setItem('selectedCharacter', JSON.stringify(character));
        this.router.navigate(['/game'], { state: { character } });
    }
}
