import { Component, OnDestroy, OnInit, inject } from '@angular/core';
import { Router } from '@angular/router';
import { Subscription } from 'rxjs';

import { CharacterPanel } from './component';
import { CharacterAttributesPanel } from './component';
import { CharacterEquipmentPanel } from './component';
import { CharacterInventoryPanel } from './component';
import { CharacterSkillsPanel } from './component';
import { CharacterWalletPanel } from './component';
import { MainPanel } from './component';
import { OptionsPanel } from './component';

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
        CharacterEquipmentPanel,
        CharacterInventoryPanel,
        CharacterSkillsPanel,
        CharacterWalletPanel,
        MainPanel,
        OptionsPanel,
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
        if (data && (data.type === 'COMBAT_ROOMS_UPDATE' || data.type === 'COMBAT_UPDATE' || data.type === 'CHARACTER_DEAD')) {
            return;
        }

        console.log(data)
        switch (data.type) {
            case 'CHARACTER_UPDATE':
                if (data.payload) {
                    this.character = data.payload as Character;
                }
                break;

            case 'CHARACTER_ATTRIBUTES_UPDATE':
                if (data.payload?.attributes) {
                    this.character = {
                        ...this.character!,
                        attributes: data.payload.attributes,
                    };
                }
                break;

            case 'CHARACTER_COMBAT_ATTRIBUTES_UPDATE':
                if (data.payload?.combatAttributes) {
                    this.character = {
                        ...this.character!,
                        combatAttributes: data.payload.combatAttributes,
                    };
                }
                break;

            case 'CHARACTER_EQUIPMENT_UPDATE':
                if (data.payload?.equipment) {
                    this.character = {
                        ...this.character!,
                        equipment: data.payload.equipment,
                    };
                }
                break;

            case 'CHARACTER_INVENTORY_UPDATE':
                if ('inventory' in data.payload) {
                    this.character = {
                        ...this.character!,
                        inventory: data.payload.inventory,
                    };
                }
                break;

            case 'CHARACTER_PROGRESSION_UPDATE':
                if (data.payload?.progression) {
                    this.character = {
                        ...this.character!,
                        progression: data.payload.progression,
                    };
                }
                break;

            case 'CHARACTER_QUESTS_UPDATE':
                if (data.payload?.quests) {
                    this.character = {
                        ...this.character!,
                        quests: data.payload.quests,
                    };
                }
                break;

            case 'CHARACTER_SPELLS_UPDATE':
                if (data.payload?.spells) {
                    this.character = {
                        ...this.character!,
                        quests: data.payload.spells,
                    };
                }
                break;

            case 'CHARACTER_SKILLS_UPDATE':
                if (Array.isArray(data.payload?.skills)) {
                    this.character = {
                        ...this.character!,
                        skills: data.payload.skills,
                    };
                }
                break;

            case 'CHARACTER_VITALS_UPDATE':
                if (data.payload?.vitals) {
                    this.character = {
                        ...this.character!,
                        vitals: data.payload.vitals,
                    };
                }
                break;

            case 'CHARACTER_WALLET_UPDATE':
                if (data.payload?.wallet) {
                    this.character = {
                        ...this.character!,
                        wallet: data.payload.wallet,
                    };
                }
                break;

            case 'CHARACTER_CURRENT_ACTION_UPDATE':
                if (data.payload?.action) {
                    this.character = {
                        ...this.character!,
                        action: data.payload.action,
                    };
                }
                break;

            case 'CHARACTER_CURRENT_COORDINATES_UPDATE': {
                if (data.payload?.coordinates) {
                    this.character = {
                        ...this.character!,
                        coordinates: data.payload.coordinates,
                    };
                }
                break;
            }

            case 'LOCATION_UPDATE':
                if (data.payload?.location) {
                    this.location = data.payload.location;
                }
                break;

            case 'LOCATION_ACTIONS_UPDATE':
                if (this.location) {
                    this.location.actions = data.payload?.actions ?? [];
                }
                break;

            case 'LOCATION_CONNECTIONS_UPDATE':
                if (this.location) {
                    this.location.connections = data.payload?.connections ?? [];
                }
                break;

            case 'LOCATION_DENIZENS_UPDATE':
                if (this.location) {
                    this.location.denizens = data.payload?.denizens ?? [];
                }
                break;

            default:
                console.warn('Unkown message:', data.type);
        }
    }

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }
}
