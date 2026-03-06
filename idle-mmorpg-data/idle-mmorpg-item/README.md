# 🗡️ idle-mmorpg-item

Defines all items that may exist in the world: consumables, equipment, weapons, off‑hands, tools, and miscellaneous objects.

## Structure

- `items.json` – flat index listing every item by its relative path.
- Subfolders by category (e.g. `consumable/`, `weapon/`, `equipment/`, `offhand/`, `tool/`, `diverse/`).
  Each file within a category defines a single item.

## Item object schema

A typical consumable item looks like:

```json
{
  "id": "food_meat",
  "type": "consumable",
  "category": "food",
  "name": "Meat",
  "description": "A simple meat.",
  "icon": "food_meat.gif",
  "price": 5,
  "effects": [
    {"type":"vital","category":"health","value":2,"duration":10},
    {"type":"vital","category":"stamina","value":2,"duration":10},
    {"type":"vital","category":"mana","value":2,"duration":10}
  ]
}
```

### Common fields

- `id`: unique string identifier.
- `type`: high‑level kind (consumable, equipment, etc.).
- `category`: further subdivision (for consumables: food, potion; for weapons: sword, axe, etc.).
- `name`, `description`, `icon`, `price`.
- `effects`: array of effect objects that modify vitals or attributes.

Effects may include `vital`, `buff`, `damage`, etc., depending on the item's purpose.

## Editing tips

- Update `items.json` whenever you add, remove, or relocate an item file.
- Maintain consistent `category` values for proper UI grouping.
- JSON formatting is forgiving but take care with commas and value types.

See the root data README or the project documentation for general guidelines.