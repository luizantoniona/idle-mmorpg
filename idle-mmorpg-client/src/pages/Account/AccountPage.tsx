import "./AccountPage.css";
import { useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";
import { useAuth } from "../../context/AuthContext";
import { APIService } from "../../service/APIService";
import { Button, PanelVertical } from "../../components";
import { CharacterList } from "./components/CharacterList";
import type { Character } from "../../models";

export function AccountPage() {
    const navigate = useNavigate();
    const { getUsername, getSessionId, logout } = useAuth();
    const [characters, setCharacters] = useState<Character[]>([]);
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState<string | null>(null);

    useEffect(() => {
        APIService.getData<{ characters: Character[] }>("/characters")
            .then((data) => {
                setCharacters(data.characters || []);
                setError(null);
            })
            .catch((err) => {
                console.error("Failed to fetch characters:", err);
                setError(err.message || "Unknown error");
            })
            .finally(() => setLoading(false));
    }, []);

    function handleStartGame(character: Character) {
        navigate("/game", { state: { character } });
    }

    return (
        <div className="account-page">
            <PanelVertical>
                <h1>Account: {getUsername()}</h1>
                <p>Session ID: {getSessionId()}</p>
                <Button
                    text="Logout"
                    onClick={logout}>
                </Button>
            </ PanelVertical>

            <PanelVertical>
                <h2>Characters</h2>
                {!loading && !error && (
                    <CharacterList characters={characters} onSelect={handleStartGame} />
                )}
                {loading && <p>Loading...</p>}
                {error && <p style={{ color: "red" }}>Error: {error}</p>}
            </PanelVertical>
        </div>
    );
}
