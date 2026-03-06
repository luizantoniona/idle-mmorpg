# ⚡ idle-mmorpg-action

Action definitions enumerate the non‑combat activities a character can perform
while idle (e.g. training, mining, etc.). These actions determine experience
gains, skill requirements, and potential item rewards.

## Structure

- `actions.json` – index listing each action path.
- `actions/*.json` – each file defines a single action and its available
  options.

## Action format

Each action file is a JSON object with the following keys:

- `id` – uppercase identifier used by the server.
- `description` – human‑readable summary.
- `options` – array of option objects representing progression tiers.

### Option fields

- `stage` – minimum world stage required to unlock the option.
- `duration` – time in seconds the action takes.
- `skill` – the skill affected or trained (e.g. `COMBAT`, `MINING`).
- `experience` – experience points awarded when the option is completed.
- `item` *(optional)* – item id dropped when finishing the action.

**Example** (`mining.json`):
```json
{
  "id": "MINING",
  "description": "Mine for minerals ore",
  "options": [
    {"stage":5,"duration":5,"skill":"MINING","experience":1,"item":"copper_ore"},
    {"stage":10,"duration":15,"skill":"MINING","experience":2,"item":"iron_ore"}
  ]
}
```

### Editing tips

- Always update `actions.json` with the relative path of any new action.
- Ensure `stage` values correspond to stage numbers defined in world data.
- Missing or malformed JSON will cause the server to skip the action.

This module currently contains `idle`, `train`, and `mining` options, but it is
meant to be easily extensible.
