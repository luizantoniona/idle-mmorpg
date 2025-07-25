import "./CharacterList.css";
import React from "react";
import { CharacterCard } from "../../molecules";
import type { Character } from "../../../models";

interface CharacterListProps {
    characters: Character[];
    onSelect: (character: Character) => void;
}

export const CharacterList: React.FC<CharacterListProps> = ({ characters, onSelect }) => {
    return (
        <div className="character-list">
            {characters.map((character, idx) => (
                <CharacterCard
                    key={character.idCharacter || idx}
                    character={character}
                    onClick={() => onSelect(character)}
                />
            ))}
        </div>
    );
};
