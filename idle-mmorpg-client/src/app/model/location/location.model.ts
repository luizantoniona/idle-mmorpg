import { LocationAction } from "./location-action.model";
import { LocationConnection } from "./location-connection.model";
import { LocationStructure } from "./location-structure.model";

export type Location = {
    id: string;
    name: string;
    description: string;
    actions: LocationAction[];
    connections: LocationConnection[];
    structures: LocationStructure[];
};
