import { useEffect, useRef, useState, useCallback } from "react";
import { useLocation } from "react-router-dom";
import { WsService } from "../../../services/WsService";
import type { Character, CharacterAttributes, CharacterWallet } from "../../../models";
import { AttributesPanel, ChatPanel, InventoryPanel, MapPanel, StatusPanel, WalletPanel } from "../../organisms/";

export function GamePage() {
    const location = useLocation();
    const character: Character = location.state.character;

    const wsRef = useRef<WsService | null>(null);
    const [connectionStatus, setConnectionStatus] = useState("Desconectado");

    const [attributes, setAttributes] = useState<CharacterAttributes>(character.attributes);
    const [wallet, setWallet] = useState<CharacterWallet>(character.wallet);
    const [inventory, setInventory] = useState([]);

    const handleMessage = useCallback((data: any) => {
        console.log("Mensagem recebida:", data);
        switch (data.type) {
            case "character_update_attributes":
                if (data.payload.attributes) {
                    setAttributes(data.payload.attributes);
                }
                break;
            case "character_update_inventory":
                if (Array.isArray(data.payload.items)) {
                    setInventory(data.payload.items);
                }
                break;
            case "character_update_wallet":
                if (data.payload.wallet) {
                    setWallet(data.payload.wallet);
                }
                break;
            case "location_update_position":
                if (data.payload.location) {
                    // Atualizar localização do personagem
                }
                break;
            default:
                console.warn("Unknow message type:", data.type);
        }
    }, []);

    const handleStatus = useCallback((status: string) => {
        const statusMap: Record<string, string> = {
            connecting: "Conectando...",
            connected: "Conectado",
            disconnected: "Desconectado",
            error: "Erro na conexão",
        };
        setConnectionStatus(statusMap[status] ?? "Desconhecido");
    }, []);

    useEffect(() => {
        if (!character?.idCharacter) return;

        const wsService = new WsService();
        wsRef.current = wsService;

        wsService.onMessage(handleMessage);
        wsService.onStatusChange(handleStatus);

        try {
            wsService.connect(character.idCharacter);
        } catch (err) {
            console.error("Erro ao conectar WebSocket:", err);
            setConnectionStatus("Erro ao conectar");
        }

        return () => {
            console.log("Fechando WebSocket");
            wsService.close();
            wsRef.current = null;
        };
    }, [character.idCharacter, handleMessage, handleStatus]);

    return (
        <div className="game-grid">
            <div className="left-sidebar">
                <StatusPanel />
                <AttributesPanel attributes={attributes} />
                <WalletPanel wallet={wallet} />
                <InventoryPanel items={inventory} />
            </div>
            <div className="main-content">
                <MapPanel />
            </div>
            <div className="right-sidebar">
                {/* <LocationPanel />
                <TabsPanel />
                <AbilitiesPanel /> */}
            </div>

            <div className="chat-bar">
                <ChatPanel />
            </div>
        </div>
    );
}
