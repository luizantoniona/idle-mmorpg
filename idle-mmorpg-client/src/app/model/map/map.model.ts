import type { MapAction } from "./map-action.model";

export type Map = {
    id: string;
    name: string;
    description: string;
    actions: MapAction[];
};
