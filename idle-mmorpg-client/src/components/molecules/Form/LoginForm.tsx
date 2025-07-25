import "./LoginForm.css";
import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import { Button, InputField, PanelVertical } from "../../atoms";
import { useAuth } from "../../../contexts/AuthContext";
import { APIService } from "../../../services/APIService";

interface LoginResponse {
    userID: number;
    username: string;
    sessionID: string;
}

export function LoginForm() {
    const [username, setUsername] = useState("");
    const [password, setPassword] = useState("");
    const [error, setError] = useState<string | null>(null);
    const { login } = useAuth();
    const navigate = useNavigate();

    async function handleSubmit(e: React.FormEvent) {
        e.preventDefault();
        setError(null);

        try {
            const loginResponse = await APIService.postData<LoginResponse>('/login', { username, password });

            if (!loginResponse || !loginResponse.sessionID || !loginResponse.userID) {
                throw new Error("Invalid login response");
            }

            login(loginResponse.userID, loginResponse.username, loginResponse.sessionID);
            navigate("/account");
        } catch (err: any) {
            console.error("Login failed:", err);
            setError(err.message || "Login failed.");
        }
    }

    return (
        <form onSubmit={handleSubmit}>
            <PanelVertical>
                <h2>Login</h2>
                <InputField
                    label="Username"
                    type="text"
                    name="username"
                    value={username}
                    onChange={(e) => setUsername(e.target.value)}
                    placeholder="Enter your username"
                />
                <InputField
                    label="Password"
                    type="password"
                    name="password"
                    value={password}
                    onChange={(e) => setPassword(e.target.value)}
                    placeholder="Enter your password"
                />
                <Button text="Login" type="submit" />
                {error && <p style={{ color: "red" }}>{error}</p>}
            </PanelVertical>
        </form>
    );
}
