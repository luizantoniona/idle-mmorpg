## 🧩 [`idle-mmorpg-data`](https://github.com/luizantoniona/idle-mmorpg/tree/main/idle-mmorpg-data)
- **Data Project**
  - Contains the static JSON definitions consumed by the server at startup.
  - Designed for easy editing, validation and expansion without recompiling.
  - Primary modules are creatures, items, spells, skills and world/stages.

Below is an overview of each package and the layout of its data files.

### 🐾 `idle-mmorpg-creature`
- `creatures.json`: index grouping creatures by type.
- `creatures/<type>/*.json`: individual creature definitions.

**Creature object example**:
```json
{
  "id": "rat",
  "name": "Rat",
  "description": "Rat.",
  "icon": "rat.gif",
  "experience": 3,
  "vitals": {"health":3,"mana":3,"stamina":3},
  "combat": {"attack":3.0,"speed":1.0},
  "loot": [
    {"id":"food_cheese","chance":0.1,"minAmount":1,"maxAmount":1},
    {"id":"coin_copper","chance":0.35,"minAmount":1,"maxAmount":1}
  ]
}
```
Fields:
- `id` (string): unique identifier used by other data.
- `vitals`, `combat` objects describe stats.
- `loot` array lists possible drops with chances/amounts.

### 🗡️ `idle-mmorpg-item`
- `items.json`: flat list of all item paths.
- Subfolders by category (consumable, equipment, weapon, offhand, tool, diverse).
  each file defines a single item.

**Item object example** (consumable food):
```json
{
  "id": "food_meat",
  "type": "consumable",
  "category": "food",
  "name": "Meat",
  "description": "A simple meat.",
  "icon": "food_meat.gif",
  "rarity": "common",
  "price": 5,
  "effects": [
    {"type":"vital","category":"health","value":2,"duration":10},
    {"type":"vital","category":"stamina","value":2,"duration":10},
    {"type":"vital","category":"mana","value":2,"duration":10}
  ]
}
```
Common fields:
- `type` identifies the high‑level kind.
- `category` further sub‑divides (e.g. food, sword).
- `effects` can modify vitals or other attributes.

### 🤺 `idle-mmorpg-skill`
- Currently only `skills.json` with list of skill IDs.
- Per‑skill files defined under folders (gathering, magic, etc.).

### 🔮 `idle-mmorpg-spell`
- `spells.json`: array of spell paths.
- `spells/*.json` – each spell defines name, cost, cooldown and effect.

**Spell example**:
```json
{
  "id": "lightning_bolt",
  "name": "Lightning Bolt",
  "description": "Strikes the target with a bolt of lightning...",
  "icon": "lightning_bolt.gif",
  "type": "attack",
  "manaCost": 10,
  "cooldown": 5,
  "effect": {"type":"damage","value":10}
}
```

### 🗺️ `idle-mmorpg-world`
- `world.json`: lists stage file paths.
- `stages/<n>.json`: defines creature pools and objectives for that stage.

**Stage example**:
```json
{
  "level": 1,
  "creatures": [{"id":"rat","amount":1}],
  "objectives": [
    {"id":"1-1","target":"rat","amount":5,
     "rewards":[{"type":"item","id":"coin_copper","amount":5}]}
  ]
}
```

Objectives allow simple quest tracking and reward specification.

---

### 🛠️ Tips for editors
- Always update the corresponding index file (`items.json`, `creatures.json`, etc.)
  when adding or removing an entry.
- Path references are relative to their parent module (e.g. `weapon/sword_iron`).
- JSON is permissive but care should be taken with commas and value types; the
  server parser performs minimal validation.
- Use the editor project or scripts (TBD) for bulk generation/balancing.
