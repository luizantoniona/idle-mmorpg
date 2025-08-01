import { Component, OnInit, inject } from '@angular/core';
import { Router } from '@angular/router';
import { CommonModule, NgIf } from '@angular/common';

import { PanelVerticalComponent } from '../../component/panel/panel-vertical.component'
import { ButtonComponent } from '../../component/button/button.component';
import { CharacterListComponent } from './component/character-list/character-list.component';

import { APIService } from '../../service/api.service';
import { AuthService } from '../../service/auth.service';
import type { Character } from '../../model';

@Component({
    selector: 'app-account-page',
    standalone: true,
    imports: [
        NgIf,
        CommonModule,
        PanelVerticalComponent,
        ButtonComponent,
        CharacterListComponent,
    ],
    templateUrl: './account.page.html',
    styleUrls: ['./account.page.scss'],
})
export class AccountPage implements OnInit {
    private router = inject(Router);
    private apiService = inject(APIService);
    private auth = inject(AuthService);

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

    getUsername(): string | null {
        return this.auth.getUsername();
    }

    getSessionId(): string | null {
        return this.auth.getSessionId();
    }

    logout(): void {
        this.auth.logout();
    }

    handleStartGame(character: Character): void {
        this.router.navigate(['/game'], { state: { character } });
    }
}
