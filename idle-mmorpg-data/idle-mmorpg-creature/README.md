# 🐾 idle-mmorpg-creature

This package contains all of the creature definitions used by the server. Creatures are the opponents and NPCs that populate stages in the game.

## Structure

- `creatures.json` – index file grouping creature paths by type.
- `creatures/<type>/*.json` – individual creature definitions. Files are arranged in subfolders according to whatever taxonomy makes sense (e.g. `animal/rat.json`, `undead/skeleton.json`).

## Creature object schema

Each creature file is a JSON object with the following fields:

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

### Fields

- `id` (string): unique identifier used by other data and systems.
- `name`, `description`, `icon`: presentation information.
- `experience`: XP awarded when defeated.
- `vitals`: base health/mana/stamina values.
- `combat`: attack power and speed modifiers.
- `loot`: array of possible drops with `chance` and quantity bounds.

## Editing tips

- Always add or remove the creature's path from `creatures.json` when modifying the folder structure.
- The server performs minimal validation; ensure correct JSON syntax.
- Subfolders are arbitrary but should help with organization.

For more information on the data format and conventions consult the top‑level data README or the project documentation.