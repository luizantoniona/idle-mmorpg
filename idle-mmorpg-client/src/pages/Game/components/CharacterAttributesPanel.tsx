import { useState, useEffect } from "react";
import { PanelVertical, Loading } from "../../../components";
import type { CharacterAttributes } from "../../../models";

interface Props {
    attributes?: CharacterAttributes;
}

export function CharacterAttributesPanel({ attributes }: Props) {
    const [state, setState] = useState<CharacterAttributes | null>(attributes || null);

    useEffect(() => {
        if (attributes) {
            setState(attributes);
        }
    }, [attributes]);

    if (!state) {
        return (
            <PanelVertical>
                <h2>Attributes</h2>
                <Loading></Loading>
            </PanelVertical>
        );
    }

    return (
        <div>
            <PanelVertical>
                <h2>Attributes</h2>
                <ul>
                    <li>Strength: {state.strength}</li>
                    <li>Dexterity: {state.dexterity}</li>
                    <li>Constitution: {state.constitution}</li>
                    <li>Intelligence: {state.intelligence}</li>
                    <li>Wisdom: {state.wisdom}</li>
                    <li>Charisma: {state.charisma}</li>
                </ul>
            </PanelVertical>
        </div>
    );
}