import { Component, Input } from '@angular/core';
import { CommonModule } from '@angular/common';

import { BarComponent, PanelVerticalComponent } from '../../../../component';

import { Character, CharacterSkill } from '../../../../model';

@Component({
    selector: 'app-character-skills-panel',
    templateUrl: './character-skills-panel.component.html',
    styleUrl: './character-skills-panel.component.scss',
    imports: [
        CommonModule,
        BarComponent,
        PanelVerticalComponent,
    ],
})

export class CharacterSkillsPanel {
    @Input() character!: Character;

    skillColors: Record<string, string> = {
        mining: '#f39c12',
        smithing: '#95a5a6',
        alchemy: '#9b59b6',
        // Cores diferentes por skill (opcional)
    };

    getProgress(characterSkill: CharacterSkill): number {
        return Math.min((characterSkill.experience / characterSkill.experienceNextLevel) * 100, 100);
    }

    getTooltip(characterSkill: CharacterSkill): string {
        return `${characterSkill.experience} / ${characterSkill.experienceNextLevel} XP`;
    }

    getSkillColor(skillId: string): string {
        return this.skillColors[skillId] ?? '#3498db'; // Cor padrão
    }
}
