import type { LocationAction } from "./location-action.model";
import type { LocationConnection } from "./location-connection.model";

export type Location = {
    id: string;
    name: string;
    description: string;
    actions: LocationAction[];
    connections: LocationConnection[];
};
