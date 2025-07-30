import { PanelVertical, Loading } from "../../atoms";
import type { CharacterAction } from "../../../models";

interface Props {
    action?: CharacterAction;
}

export function CharacterActionPanel({ action }: Props) {
    return (
        <div>
            <PanelVertical>
                <h2>Current Action</h2>
            </PanelVertical>
        </div>
    );
}