import { Component, Input } from '@angular/core';
import { CommonModule } from '@angular/common';

import { BarComponent } from '../../../../component';
import { PanelComponent } from '../../../../component';
import { TooltipComponent } from '../../../../component';

import { Character, CharacterSkill } from '../../../../model';

@Component({
    selector: 'app-character-skills-panel',
    templateUrl: './character-skills-panel.component.html',
    styleUrl: './character-skills-panel.component.scss',
    imports: [
        CommonModule,
        BarComponent,
        PanelComponent,
        TooltipComponent,
    ],
})

export class CharacterSkillsPanel {
    @Input() character!: Character;

    getProgress(characterSkill: CharacterSkill): number {
        return Math.min((characterSkill.experience / characterSkill.experienceNextLevel) * 100, 100);
    }

    getTooltip(characterSkill: CharacterSkill): string {
        return `${characterSkill.experience} / ${characterSkill.experienceNextLevel} XP`;
    }

    groupSkillsByCategory(skills: any[]): Map<string, any[]> {
        const groups = new Map<string, any[]>();

        for (const skill of skills) {
            const category = skill.skill.type || 'Uncategorized';
            if (!groups.has(category)) {
                groups.set(category, []);
            }
            groups.get(category)!.push(skill);
        }

        return groups;
    }
}
