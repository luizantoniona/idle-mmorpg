import { Action } from "../";

export type CharacterAction = {
    currentAction: Action;
    availableActions: Action[];

    duration: number;
    counter: number;
};
