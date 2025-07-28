import { PanelVertical } from "../../atoms";
import type { Character } from "../../../models";

interface Props {
    character: Character | null;
}

export function StatusPanel({ character }: Props) {
    return (
        <PanelVertical>
            <h2>{character?.name}</h2>
        </PanelVertical>
    );
}
