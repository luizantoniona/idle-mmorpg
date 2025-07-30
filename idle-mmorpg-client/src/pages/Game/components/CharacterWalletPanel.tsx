import { useEffect, useState } from "react";
import { PanelVertical, Loading } from "../../../components";
import type { CharacterWallet } from "../../../models";

interface Props {
    wallet?: CharacterWallet;
}

export function CharacterWalletPanel({ wallet }: Props) {
    const [state, setState] = useState<CharacterWallet | null>(wallet || null);

    useEffect(() => {
        if (wallet) {
            setState(wallet);
        }
    }, [wallet]);

    if (!state) {
        return (
            <PanelVertical>
                <h2>Wallet</h2>
                <Loading></Loading>
            </PanelVertical>
        );
    }

    return (
        <PanelVertical>
            <h2>Wallet</h2>
            <li>Ouro: {state.gold}</li>
            <li>Prata: {state.silver}</li>
            <li>Cobre: {state.copper}</li>
        </PanelVertical>
    );
}
