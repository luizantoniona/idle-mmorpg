import type { MapAction } from "./map-action";

export type Map = {
    id: string;
    name: string;
    description: string;
    actions: MapAction[];
};