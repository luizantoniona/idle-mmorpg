# 🔮 idle-mmorpg-spell

Spells define magical abilities available to players and creatures. Each spell includes cost, cooldown, and effects.

## Structure

- `spells.json` – index array of every spell path.
- `spells/*.json` – individual spell definitions.

## Spell object example

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

### Common fields

- `id`, `name`, `description`, `icon`.
- `type`: attack, heal, buff, etc.
- `manaCost`, `staminaCost`, or other resource requirements.
- `cooldown`: time in seconds before reuse.
- `effect` / `effects`: describes damage, healing, buffs, debuffs, area of effect, and so on.

## Editing tips

- Add or remove the spell's path in `spells.json` when creating/deleting files.
- Keep the format consistent with existing spells to ease server parsing.
- Validate JSON syntax; the server does not guard against malformed data.

Further guidelines live in the root data README.