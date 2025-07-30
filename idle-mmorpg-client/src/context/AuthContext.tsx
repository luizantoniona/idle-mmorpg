import React, { createContext, useContext, useEffect, useState } from "react";
import { APIService } from "../service/APIService";
import { AuthManager } from "../manager/AuthManager";
import type { AuthData } from "../manager/AuthManager";

interface AuthContextValue {
    auth: AuthData | null;
    login: (userID: number, username: string, sessionID: string) => void;
    logout: () => void;
    isLoggedIn: () => boolean;
    getUserId: () => number | null;
    getUsername: () => string | null;
    getSessionId: () => string | null;
}

const AuthContext = createContext<AuthContextValue | undefined>(undefined);

export function AuthProvider({ children }: { children: React.ReactNode }) {
    const [auth, setAuth] = useState<AuthData | null>(() => AuthManager.get());

    useEffect(() => {
        if (auth?.sessionID) {
            APIService.setAuthToken(auth.sessionID);
        }
    }, [auth]);

    const login = (userID: number, username: string, sessionID: string) => {
        const data = { userID, username, sessionID };
        AuthManager.login(data);
        APIService.setAuthToken(sessionID);
        setAuth(data);
    };

    const logout = () => {
        AuthManager.logout();
        APIService.clearAuthToken();
        setAuth(null);
    };

    return (
        <AuthContext.Provider
            value={{
                auth,
                login,
                logout,
                isLoggedIn: () => !!auth?.sessionID,
                getUserId: () => auth?.userID ?? null,
                getUsername: () => auth?.username ?? null,
                getSessionId: () => auth?.sessionID ?? null,
            }}
        >
            {children}
        </AuthContext.Provider>
    );
}

export function useAuth(): AuthContextValue {
    const context = useContext(AuthContext);
    if (!context) {
        throw new Error("useAuth must be used within an AuthProvider");
    }
    return context;
}