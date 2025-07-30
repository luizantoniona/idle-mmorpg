import { useCallback, useEffect, useRef, useState } from "react";
import { WsService } from "../../../services/WsService";
import type { Character, Map } from "../../../models";

export function GamePageHooks(initialCharacter: Character) {
    const websocket = useRef<WsService | null>(null);
    const [character, setCharacter] = useState<Character>(initialCharacter);
    const [map, setMap] = useState<Map | null>(null);
    const [connectionStatus, setConnectionStatus] = useState("Desconectado");

    const handleMessage = useCallback((data: any) => {
        switch (data.type) {
            case "character_update_action":
                if (data.payload.action) {
                    setCharacter((prev) => ({
                        ...prev,
                        action: data.payload.action,
                    }));
                }
                break;

            case "character_update_attributes":
                if (data.payload.attributes) {
                    setCharacter((prev) => ({
                        ...prev,
                        attributes: data.payload.attributes,
                    }));
                }
                break;

            case "character_update_skills":
                if (Array.isArray(data.payload.skills)) {
                    setCharacter((prev) => ({
                        ...prev,
                        skills: data.payload.skills,
                    }));
                }
                break;

            case "character_update_wallet":
                if (data.payload.wallet) {
                    setCharacter((prev) => ({
                        ...prev,
                        wallet: data.payload.wallet,
                    }));
                }
                break;

            case "location_update_position":
                if (data.payload.location) {
                    setMap(data.payload.location);
                }
                break;

            case "location_update_actions":
                if (Array.isArray(data.payload.actions)) {
                    setMap((prev) =>
                        prev
                            ? {
                                ...prev,
                                actions: data.payload.actions,
                            }
                            : prev
                    );
                }
                break;

            default:
                console.warn("Mensagem desconhecida:", data.type);
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
        if (!initialCharacter?.idCharacter) return;

        const wsService = new WsService();
        websocket.current = wsService;

        wsService.onMessage(handleMessage);
        wsService.onStatusChange(handleStatus);

        try {
            wsService.connect(initialCharacter.idCharacter);
        } catch (err) {
            console.error("Erro ao conectar WebSocket:", err);
            setConnectionStatus("Erro");
        }

        return () => {
            wsService.close();
            websocket.current = null;
        };
    }, [initialCharacter?.idCharacter, handleMessage, handleStatus]);

    const sendMessage = (msg: any) => {
        websocket.current?.send(msg);
    };

    return {
        character,
        map,
        connectionStatus,
        sendMessage,
    };
}
