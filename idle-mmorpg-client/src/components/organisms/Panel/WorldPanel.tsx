import { Button, PanelVertical, Loading } from "../../atoms";
import type { Map } from "../../../models";
import { WsService } from "../../../services/WsService";

interface Props {
    map: Map | null;
    ws: WsService | null;
}

export function WorldPanel({ map, ws }: Props) {
    if (!map) {
        return (
            <PanelVertical>
                <h2>Map</h2>
                <Loading></Loading>
            </PanelVertical>
        );
    }

    return (
        <PanelVertical>
            <h2>{map.name}</h2>
            <p>{map.description}</p>

            <hr />
            <h3>Actions</h3>

            {map.actions?.length ? (
                map.actions.map((action) => (
                    <Button
                        key={action.id}
                        text={action.label}
                        onClick={() => ws?.send({
                            type: "character_update_action",
                            payload: { id: action.id },
                        })}
                    />
                ))
            ) : (
                <p>No actions</p>
            )}
        </PanelVertical>
    );
}