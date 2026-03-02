import { Component, OnDestroy, OnInit, inject } from "@angular/core";
import { Router } from "@angular/router";
import { Subscription } from "rxjs";

import {
    CharacterActionPanel, CharacterDataPanel, CharacterEquipmentPanel, CharacterInventoryPanel,
    CharacterSkillsPanel, CharacterSpellsPanel,
    CombatPanel, OptionsPanel, StagePanel
} from "./component";

import { Character, CombatInstance, Stage } from "../../model";

import { WebsocketService } from "../../service";

@Component({
    selector: "app-game-page",
    templateUrl: "./game.page.html",
    styleUrls: ["./game.page.scss"],
    imports: [
        CharacterActionPanel,
        CharacterDataPanel,
        CharacterEquipmentPanel,
        CharacterInventoryPanel,
        CharacterSkillsPanel,
        CharacterSpellsPanel,
        CombatPanel,
        OptionsPanel,
        StagePanel
    ],
})

export class GamePage implements OnInit, OnDestroy {
    private router = inject(Router);
    private websocketService = inject(WebsocketService);

    character: Character | null = null;
    stage: Stage | null = null;
    combatInstances: CombatInstance[] = [];

    connectionStatus = 'Desconectado';

    private subscriptions = new Subscription();

    ngOnInit(): void {
        const navState = this.router.currentNavigation()?.extras.state;
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
        console.log('Message:', data);
        switch (data.type) {
            case 'CHARACTER':
                if (data.payload) {
                    this.character = data.payload as Character;
                }
                break;

            case 'CHARACTER_ACTIONS':
                if (data.payload?.actions) {
                    this.character = {
                        ...this.character!,
                        actions: data.payload.actions,
                    };
                }
                break;

            case 'CHARACTER_EFFECTS':
                if (Array.isArray(data.payload?.effects)) {
                    this.character = {
                        ...this.character!,
                        effects: data.payload.effects,
                    };
                }
                break;

            case 'CHARACTER_EQUIPMENT':
                if (data.payload?.equipment) {
                    this.character = {
                        ...this.character!,
                        equipment: data.payload.equipment,
                    };
                }
                break;

            case 'CHARACTER_INVENTORY':
                if ('inventory' in data.payload) {
                    this.character = {
                        ...this.character!,
                        inventory: data.payload.inventory,
                    };
                }
                break;

            case 'CHARACTER_PROGRESSION':
                if (data.payload?.progression) {
                    this.character = {
                        ...this.character!,
                        progression: data.payload.progression,
                    };
                }
                break;

            case 'CHARACTER_SKILLS':
                if (Array.isArray(data.payload?.skills)) {
                    this.character = {
                        ...this.character!,
                        skills: data.payload.skills,
                    };
                }
                break;

            case 'CHARACTER_SPELLS':
                if (data.payload?.spells) {
                    this.character = {
                        ...this.character!,
                        spells: data.payload.spells,
                    };
                }
                break;

            case 'CHARACTER_VITALS':
                if (data.payload?.vitals) {
                    this.character = {
                        ...this.character!,
                        vitals: data.payload.vitals,
                    };
                }
                break;

            case 'CHARACTER_WALLET':
                if (data.payload?.wallet) {
                    this.character = {
                        ...this.character!,
                        wallet: data.payload.wallet,
                    };
                }
                break;

            case 'STAGE':
                if (data.payload?.stage) {
                    this.stage = data.payload.stage;
                }
                if (this.stage) {
                    this.stage.objectives = data.payload?.objectives ?? [];
                }
                break;

            default:
                break;
        }
    }

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }
}
