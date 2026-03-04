import { Action } from "../";

export type CharacterActions = {
    currentAction: Action;
    availableActions: Action[];

    duration: number;
    counter: number;
};
