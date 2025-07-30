import { useState, useEffect } from "react";
import type { CharacterInventory } from "../../../models";

interface Props {
    inventory?: CharacterInventory;
}

export function CharacterInventoryPanel({ inventory }: Props) {
    return (
        <div>
            <h2>Inventory</h2>
        </div>
    );
}
