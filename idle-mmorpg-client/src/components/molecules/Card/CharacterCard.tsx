import "./CharacterCard.css";
import React from "react";
import type { Character } from "../../../models";

interface CharacterCardProps {
    character: Character;
    onClick?: () => void;
}

export const CharacterCard: React.FC<CharacterCardProps> = ({ character, onClick }) => {
    const { name, attributes } = character;

    return (
        <div className="character-card" onClick={onClick}>
            <div className="character-header">
                <h3>{name}</h3>
            </div>
            {attributes ? (<div className="character-attributes">
                <p><strong>STR</strong>: {attributes.strength}</p>
                <p><strong>DEX</strong>: {attributes.dexterity}</p>
                <p><strong>CON</strong>: {attributes.constitution}</p>
                <p><strong>INT</strong>: {attributes.intelligence}</p>
                <p><strong>WIS</strong>: {attributes.wisdom}</p>
                <p><strong>CHA</strong>: {attributes.charisma}</p>
            </div>) : (<div className=".character-header">
                <p>No attributes.</p>
            </div>
            )}
        </div>
    );
};