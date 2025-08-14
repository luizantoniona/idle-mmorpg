import { Denizen } from "../denizen/denizen.model";
import { LocationAction } from "./location-action.model";
import { LocationConnection } from "./location-connection.model";
import { LocationStructure } from "./location-structure.model";

export type Location = {
    id: string;
    name: string;
    description: string;
    denizens: Denizen[];
    actions: LocationAction[];
    connections: LocationConnection[];
    structures: LocationStructure[];
};
