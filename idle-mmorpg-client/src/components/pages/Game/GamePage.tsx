import { useLocation } from "react-router-dom";
import { GamePageHooks } from "./GamePageHooks";
import type { Character } from "../../../models";

export function GamePage() {
    const location = useLocation();
    const initialCharacter = location.state?.character as Character;

    const {
        character,
        map,
        connectionStatus,
        sendMessage,
    } = GamePageHooks(initialCharacter);

    return (
        <div className="game-grid">
            <div className="left-sidebar">
                {/* <CharacterAttributesPanel attributes={character.attributes} /> */}
            </div>
            <div className="main-content">
                {/* <WorldPanel map={map} onActionSelect={...} /> */}
            </div>
            <div className="right-sidebar">
                {/* <WalletPanel wallet={character.wallet} /> */}
            </div>
            <div className="chat-bar">
                {/* <ChatPanel /> */}
            </div>
        </div>
    );
}
