import type { MapAction } from "./MapAction";

export type Map = {
    id: string;
    name: string;
    description: string;
    actions: MapAction[];
};