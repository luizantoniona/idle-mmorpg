import { PanelVertical, Loading } from "../../../components";
import type { CharacterInventory } from "../../../models";

interface Props {
    inventory?: CharacterInventory;
}

export function CharacterInventoryPanel({ inventory }: Props) {
    return (
        <div>
            <PanelVertical>
                <h2>INVENTORY</h2>
            </PanelVertical>
        </div>
    );
}
