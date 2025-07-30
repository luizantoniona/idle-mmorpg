import "./GamePage.css"
import { useLocation } from "react-router-dom";
import { GamePageHooks } from "./GamePageHooks";
import { CharacterAttributesPanel, CharacterEquipamentPanel, CharacterInventoryPanel, CharacterSkillsPanel, CharacterVitalsPanel, CharacterWalletPanel } from "./components";
import { ChatPanel } from "./components/ChatPanel";
import type { Character } from "../../models";

export function GamePage() {
    const location = useLocation();
    const initialCharacter = location.state?.character as Character;

    // const {
    //     character,
    //     map,
    //     connectionStatus,
    //     sendMessage,
    // } = GamePageHooks(initialCharacter);

    return (
        <div className="game-row">
            <div className="left-sidebar">
                <CharacterVitalsPanel></CharacterVitalsPanel>
                <CharacterAttributesPanel></CharacterAttributesPanel>
                <CharacterSkillsPanel></CharacterSkillsPanel>
            </div>
            <div className="main-content">
                <ChatPanel></ChatPanel>
            </div>
            <div className="right-sidebar">
                <CharacterWalletPanel></CharacterWalletPanel>
                <CharacterEquipamentPanel></CharacterEquipamentPanel>
                <CharacterInventoryPanel></CharacterInventoryPanel>
            </div>
        </div>
    );
}
