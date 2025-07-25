import "./ServerForm.css";
import React, { useState, useEffect } from "react";
import { Button, InputField, PanelHorizontal, StatusCircle } from "../../atoms";
import { useServer } from "../../../contexts/ServerContext";
import { APIService } from "../../../services/APIService";

export function ServerForm() {
    const { connect, server } = useServer();
    const [ip, setIp] = useState(server?.address || "");
    const [port, setPort] = useState(server?.port || "");
    const [status, setStatus] = useState<"online" | "offline" | "loading" | "error" | "unknown">(
        server ? "loading" : "offline"
    );
    const [error, setError] = useState<string | null>(null);

    useEffect(() => {
        if (server) checkStatus();
    }, [server]);

    async function checkStatusWithParams(ip: string, port: string): Promise<boolean> {
        try {
            const tempUrl = `http://${ip.replace(/^https?:\/\//, "")}:${port}`;
            const response = await fetch(`${tempUrl}/status`);
            if (!response.ok) throw new Error();
            setStatus("online");
            return true;
        } catch {
            setStatus("error");
            return false;
        }
    }

    async function checkStatus() {
        try {
            await APIService.getStatus();
            setStatus("online");
        } catch {
            setStatus("error");
        }
    }

    async function handleSubmit(e: React.FormEvent) {
        e.preventDefault();
        setError(null);
        setStatus("loading");

        const ok = await checkStatusWithParams(ip, port);
        if (!ok) {
            setError("Could not connect to the server.");
            return;
        }

        connect(ip, port);
    }

    return (
        <div className="server-form-wrapper">
            <form onSubmit={handleSubmit}>
                <PanelHorizontal>
                    <h2>Server:</h2>
                    <StatusCircle status={status} />
                    <InputField
                        label="IP Address"
                        name="ip"
                        value={ip}
                        onChange={(e) => setIp(e.target.value)}
                        placeholder="127.0.0.1"
                    />
                    <InputField
                        label="Port"
                        name="port"
                        value={port}
                        onChange={(e) => setPort(e.target.value)}
                        placeholder="8080"
                    />
                    <Button text={server ? "Reconnect" : "Connect"} type="submit" />
                    {error && <p style={{ color: "red" }}>{error}</p>}
                </PanelHorizontal>
            </form>
        </div>
    );
}
