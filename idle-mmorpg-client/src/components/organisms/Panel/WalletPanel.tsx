import { useEffect, useState } from "react";
import type { CharacterWallet } from "../../../models";
import { PanelVertical, Loading } from "../../atoms";

interface Props {
    wallet?: CharacterWallet;
}

export function WalletPanel({ wallet }: Props) {
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
        <div>
            <PanelVertical>
                <h2>Carteira</h2>
            </PanelVertical>
            <ul>
                <li>Ouro: {state.gold}</li>
                <li>Prata: {state.silver}</li>
                <li>Cobre: {state.copper}</li>
            </ul>
        </div>
    );
}