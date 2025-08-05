import { Skill } from "../skill/skill.model";

export type CharacterSkill = {
    id: string;
    level: number;
    experience: number;
    experienceNextLevel: number;
    skill: Skill;
};
