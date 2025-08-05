import { Component, OnDestroy, OnInit, inject } from '@angular/core';
import { Router } from '@angular/router';
import { Subscription } from 'rxjs';

import { CharacterPanel } from './component';
import { CharacterAttributesPanel } from './component';
import { CharacterEquipamentPanel } from './component';
import { CharacterInventoryPanel } from './component';
import { CharacterSkillsPanel } from './component';
import { CharacterWalletPanel } from './component';
import { ChatPanel } from './component';
import { LocationPanel } from './component';

import { Character } from '../../model';
import { Location } from '../../model';

import { WebsocketService } from '../../service/websocket.service';

@Component({
    selector: 'app-game-page',
    templateUrl: './game.page.html',
    styleUrl: './game.page.scss',
    imports: [
        CharacterPanel,
        CharacterAttributesPanel,
        CharacterEquipamentPanel,
        CharacterInventoryPanel,
        CharacterSkillsPanel,
        CharacterWalletPanel,
        ChatPanel,
        LocationPanel,
    ],
})

export class GamePage implements OnInit, OnDestroy {
    private router = inject(Router);
    private websocketService = inject(WebsocketService);

    character: Character | null = null;
    location: Location | null = null;
    connectionStatus = 'Desconectado';

    private subscriptions = new Subscription();

    ngOnInit(): void {
        const navState = this.router.getCurrentNavigation()?.extras.state;
        const passedCharacter = navState?.['character'] as Character | undefined;

        if (passedCharacter) {
            this.character = passedCharacter;
            localStorage.setItem('selectedCharacter', JSON.stringify(passedCharacter));
        } else {
            const stored = localStorage.getItem('selectedCharacter');
            if (stored) {
                try {
                    this.character = JSON.parse(stored);
                } catch (err) {
                    console.error('Failed to parse stored character:', err);
                }
            }
        }

        if (!this.character) {
            console.error('Character data not found in navigation state or storage.');
            this.router.navigate(['/']);
            return;
        }

        this.subscriptions.add(
            this.websocketService.messages$.subscribe((msg) => this.handleMessage(msg))
        );

        this.subscriptions.add(
            this.websocketService.status$.subscribe((status) => this.handleStatus(status))
        );

        try {
            this.websocketService.connect(this.character.idCharacter);

        } catch (err) {
            console.error('Erro ao conectar WebSocket:', err);
            this.connectionStatus = 'Erro';
            this.router.navigate(['/account']);
        }
    }

    ngOnDestroy(): void {
        this.subscriptions.unsubscribe();
        this.websocketService.close();
    }

    handleMessage(data: any): void {
        console.log(data)
        switch (data.type) {
            case 'character_update':
                if (data.payload) {
                    this.character = data.payload as Character;
                }
                break;

            case 'character_update_action':
                if (data.payload?.action) {
                    this.character = {
                        ...this.character!,
                        action: data.payload.action,
                    };
                }
                break;

            case 'character_update_attributes':
                if (data.payload?.attributes) {
                    this.character = {
                        ...this.character!,
                        attributes: data.payload.attributes,
                    };
                }
                break;

            case 'character_update_equipament':
                if (data.payload?.equipament) {
                    this.character = {
                        ...this.character!,
                        equipament: data.payload.equipament,
                    };
                }
                break;

            case 'character_update_inventory':
                if (data.payload?.inventory) {
                    this.character = {
                        ...this.character!,
                        inventory: data.payload.inventory,
                    };
                }
                break;

            case 'character_update_progression':
                if (data.payload?.progression) {
                    this.character = {
                        ...this.character!,
                        progression: data.payload.progression,
                    };
                }
                break;

            case 'character_update_skills':
                if (Array.isArray(data.payload?.skills)) {
                    this.character = {
                        ...this.character!,
                        skills: data.payload.skills,
                    };
                }
                break;

            case 'character_update_vitals':
                if (data.payload?.vitals) {
                    this.character = {
                        ...this.character!,
                        vitals: data.payload.vitals,
                    };
                }
                break;

            case 'character_update_wallet':
                if (data.payload?.wallet) {
                    this.character = {
                        ...this.character!,
                        wallet: data.payload.wallet,
                    };
                }
                break;

            case 'location_update_position':
                if (data.payload?.location) {
                    this.location = data.payload.location;
                }
                break;

            case 'location_update_actions':
                if (Array.isArray(data.payload?.actions)) {
                    this.location = this.location
                        ? { ...this.location, actions: data.payload.actions }
                        : this.location;
                }
                break;

            default:
                console.warn('Unkown message:', data.type);
        }
    }

    handleStatus(status: string): void {
        const statusMap: Record<string, string> = {
            connecting: 'Conectando...',
            connected: 'Conectado',
            disconnected: 'Desconectado',
            error: 'Erro na conexão',
        };
        this.connectionStatus = statusMap[status] ?? 'Desconhecido';
    }

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    onActionClick(actionId: string): void {
        if (!this.character) return;
        this.sendMessage({
            type: 'character_update_action',
            payload: {
                actionId: actionId,
            },
        });
    }

    onConnectionClick(destination: string): void {
        if (!this.character) return;
        this.sendMessage({
            type: 'character_update_location',
            payload: {
                destination: destination,
            },
        });
    }
}
