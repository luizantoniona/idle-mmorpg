import { Skill } from "../skill/skill.model";

export type CharacterSkill = {
    id: string;
    level: number;
    bonusLevel: number;
    experience: number;
    experienceNextLevel: number;
    skill: Skill;
};
