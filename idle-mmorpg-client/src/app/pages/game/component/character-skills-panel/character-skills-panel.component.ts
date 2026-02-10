import { Component, Input } from "@angular/core";
import { CommonModule } from "@angular/common";

import { BarComponent, PanelComponent, TooltipComponent } from "../../../../component/ui";

import { Character, CharacterSkill } from "../../../../model";

@Component({
    selector: "app-character-skills-panel",
    templateUrl: "./character-skills-panel.component.html",
    styleUrls: ["./character-skills-panel.component.scss"],
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
            const category = skill.skill.category || 'Uncategorized';
            if (!groups.has(category)) {
                groups.set(category, []);
            }
            groups.get(category)!.push(skill);
        }

        return groups;
    }
}
