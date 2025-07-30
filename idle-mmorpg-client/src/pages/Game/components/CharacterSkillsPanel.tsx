import { PanelVertical } from "../../atoms";
import type { CharacterSkill } from "../../../models";

interface Props {
    skills?: CharacterSkill[];
}

export function CharacterSkillsPanel({ skills }: Props) {
    return (
        <PanelVertical>
            <h2>Character Skills</h2>
        </PanelVertical>
    );
}
