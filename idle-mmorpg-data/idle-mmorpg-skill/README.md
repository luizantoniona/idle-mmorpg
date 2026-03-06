# 🤺 idle-mmorpg-skill

Skill definitions encompass all non‑magical abilities a player or NPC can use.

## Structure

- `skills.json` – simple list of skill identifiers (paths).
- Folders under the main directory group skills by type, such as `gathering/`, `magic/`, `vitals/`, `weapon/`, etc. Each JSON file inside defines one skill.

## Skill object overview

Skills vary widely, but they typically include fields like:

- `id`, `name`, `description`, `icon`
- `cost` (stamina, energy, etc.)
- `cooldown`, `duration`
- `effect` or `effects` describing what the skill does (e.g. damage, heal, buff).

Since the format is flexible, inspect existing skill files for examples when adding new ones.

## Editing tips

- Add the skill's path to `skills.json` after creating the file.
- Place skills in an appropriate subfolder to keep the directory organised.
- The server parser performs minimal validation; use a linter or editor to verify JSON syntax.

Refer to the top‑level data README for general conventions.