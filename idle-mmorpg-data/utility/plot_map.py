import os
import json
import plotly.graph_objects as go
import plotly.io as pio
import random

pio.renderers.default = "browser"

BASE_PATH = os.path.join(os.path.dirname(__file__), "..", "World")
CONFIG_PATH = os.path.join(os.path.dirname(__file__), "..", "config.json")


def load_world_map():
    with open(CONFIG_PATH, "r") as f:
        return json.load(f)


def load_region(region_name):
    path = os.path.join(BASE_PATH, region_name, "config.json")
    with open(path, "r") as f:
        return json.load(f)


def load_area(region_name, area_id):
    path = os.path.join(BASE_PATH, region_name, "Areas", f"{area_id}.json")
    with open(path, "r") as f:
        return json.load(f)


def random_color():
    return f"rgb({random.randint(50,200)}, {random.randint(50,200)}, {random.randint(50,200)})"


def build_graph(world_data):
    nodes = []
    edges_intra = []
    edges_inter = []
    region_colors = {}

    for region_name in world_data["regions"]:
        region = load_region(region_name)
        region_color = random_color()
        region_colors[region_name] = region_color

        for location_id in region["locations"]:
            area = load_area(region_name, location_id)
            coord = area["coordinates"]
            nodes.append(
                {
                    "id": area["id"],
                    "name": area["name"],
                    "region": region_name,
                    "x": coord["x"],
                    "y": coord["y"],
                    "z": coord["z"],
                    "color": region_color,
                }
            )

        for conn in region.get("connections", []):
            edges_intra.append((conn["origin"], conn["destination"]))

    for conn in world_data.get("connections", []):
        edges_inter.append((conn["origin"], conn["destination"]))

    return nodes, edges_intra, edges_inter


def visualize_graph_3d(nodes, edges_intra, edges_inter):
    fig = go.Figure()

    grouped = {}
    for node in nodes:
        grouped.setdefault(node["region"], []).append(node)

    for region, region_nodes in grouped.items():
        fig.add_trace(
            go.Scatter3d(
                x=[n["x"] for n in region_nodes],
                y=[n["y"] for n in region_nodes],
                z=[n["z"] for n in region_nodes],
                mode="markers+text",
                marker=dict(size=6, color=region_nodes[0]["color"]),
                text=[f'{n["name"]} ({n["region"]})' for n in region_nodes],
                textposition="top center",
                name=region,
            )
        )

    node_map = {n["id"]: n for n in nodes}

    for origin_id, dest_id in edges_intra:
        if origin_id in node_map and dest_id in node_map:
            a, b = node_map[origin_id], node_map[dest_id]
            fig.add_trace(
                go.Scatter3d(
                    x=[a["x"], b["x"]],
                    y=[a["y"], b["y"]],
                    z=[a["z"], b["z"]],
                    mode="lines",
                    line=dict(width=3, color="gray"),
                    name=f"{a['region']} connection",
                    showlegend=False,
                )
            )

    for origin_id, dest_id in edges_inter:
        if origin_id in node_map and dest_id in node_map:
            a, b = node_map[origin_id], node_map[dest_id]
            fig.add_trace(
                go.Scatter3d(
                    x=[a["x"], b["x"]],
                    y=[a["y"], b["y"]],
                    z=[a["z"], b["z"]],
                    mode="lines",
                    line=dict(width=2, color="red", dash="dash"),
                    name="Global connection",
                    showlegend=False,
                )
            )
        else:
            print(f"[WARN] Global connection skipped: {origin_id} -> {dest_id} (missing area)")

    fig.update_layout(
        title="🌍 Idle MMORPG World Map (3D)",
        scene=dict(xaxis_title="X", yaxis_title="Y", zaxis_title="Z"),
        margin=dict(l=0, r=0, b=0, t=40),
        legend=dict(itemsizing="constant"),
    )

    fig.show()


if __name__ == "__main__":
    world_data = load_world_map()
    nodes, edges_intra, edges_inter = build_graph(world_data)
    visualize_graph_3d(nodes, edges_intra, edges_inter)
