import json
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import os

region = "astrya"
area = "heroes_path"

input_path = f"../idle-mmorpg-map/world/{region}/areas/{area}/tileset.json"
input_asset_path = "../../idle-mmorpg-client/src/assets/tileset"
tile_size = 32

with open(input_path, "r") as f:
    map_data = json.load(f)

layers = sorted(map_data["layers"], key=lambda l: l["z"])

height = len(layers[0]["tiles"])
width = len(layers[0]["tiles"][0])

canvas = np.zeros((height * tile_size, width * tile_size, 4), dtype=np.float32)

tile_cache = {}
def get_tile(tile_id: int):
    if tile_id in tile_cache:
        return tile_cache[tile_id]

    path = os.path.join(input_asset_path, f"{tile_id}.png")
    if os.path.exists(path):
        tile_cache[tile_id] = mpimg.imread(path)
    else:
        tile_cache[tile_id] = np.zeros((tile_size, tile_size, 4), dtype=np.float32)
        print(f"[WARN] missing tile asset: {path}")
    return tile_cache[tile_id]

for layer in layers:
    grid = np.array(layer["tiles"])
    for y in range(height):
        for x in range(width):
            tile_id = grid[y, x]
            if tile_id == 0:
                continue
            tile_img = get_tile(tile_id)

            y0, x0 = y * tile_size, x * tile_size
            y1, x1 = y0 + tile_size, x0 + tile_size

            canvas[y0:y1, x0:x1] = tile_img

plt.figure(figsize=(8, 8))
plt.imshow(canvas)
plt.axis("off")
plt.title("Rendered")
plt.show()