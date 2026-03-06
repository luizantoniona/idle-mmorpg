# 🗺️ idle-mmorpg-world

World data defines the stages, creature pools, and objectives for the game.

## Structure

- `world.json` – list of stage file paths.
- `stages/<n>.json` – stage definitions, where `<n>` is typically the stage number.

## Stage object example

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

### Fields

- `level`: numerical indicator of stage difficulty or order.
- `creatures`: array of creature IDs and spawn amounts.
- `objectives`: optional list of simple quests, each with an `id`, `target`, `amount`, and `rewards` array.

Objectives enable basic quest tracking and reward specification.

## Editing tips

- Update `world.json` whenever adding or removing a stage file path.
- Keep stage numbering sequential for clarity.
- Validate JSON syntax; the server will load stages at startup without deep checks.

See the main data README for general information and project‑wide conventions.