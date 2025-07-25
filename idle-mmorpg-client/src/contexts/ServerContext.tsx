import React, { createContext, useContext, useState } from "react";
import { ServerManager } from "../managers/ServerManager";
import type { ServerData } from "../managers/ServerManager";

interface ServerContextValue {
    server: ServerData | null;
    connect: (address: string, port: string) => void;
    disconnect: () => void;
    getAddress: () => string | null;
    getPort: () => string | null;
}

const ServerContext = createContext<ServerContextValue | undefined>(undefined);

export function ServerProvider({ children }: { children: React.ReactNode }) {
    const [server, setServer] = useState<ServerData | null>(() => ServerManager.get());

    const connect = (address: string, port: string) => {
        const data = { address, port };
        ServerManager.connect(data);
        setServer(data);
    };

    const disconnect = () => {
        ServerManager.disconnect();
        setServer(null);
    };

    return (
        <ServerContext.Provider
            value={{
                server,
                connect,
                disconnect,
                getAddress: () => server?.address ?? null,
                getPort: () => server?.port ?? null,
            }}
        >
            {children}
        </ServerContext.Provider>
    );
}

export function useServer(): ServerContextValue {
    const context = useContext(ServerContext);
    if (!context) {
        throw new Error("useServer must be used within a ServerProvider");
    }
    return context;
}
