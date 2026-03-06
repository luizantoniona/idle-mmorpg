## 🧩 [`idle-mmorpg-data`](https://github.com/luizantoniona/idle-mmorpg/tree/main/idle-mmorpg-data)

This package stores all of the static JSON content consumed by the server at
startup. Data is split into five logical modules; each has its own README with
schema details and examples.

### ✅ Modules

- [🐾 `idle-mmorpg-creature`](./idle-mmorpg-creature/README.md) – creatures and
  their stats, loot, and metadata.
- [🗡️ `idle-mmorpg-item`](./idle-mmorpg-item/README.md) – consumables,
  equipment, weapons, tools, etc.
- [⚡ `idle-mmorpg-action`](./idle-mmorpg-action/README.md) – idle activities and
  experience options.
- [🤺 `idle-mmorpg-skill`](./idle-mmorpg-skill/README.md) – non‑magical abilities.
- [🔮 `idle-mmorpg-spell`](./idle-mmorpg-spell/README.md) – magical spells.
- [🗺️ `idle-mmorpg-world`](./idle-mmorpg-world/README.md) – stages,
  creature pools, and objectives.
- [⚙️ `idle-mmorpg-configuration`](./idle-mmorpg-configuration/README.md) – global
  tuning parameters and logo asset.

Each module index file (`*.json`) must be kept in sync when you add or remove
entries. The server performs only minimal validation, so correct JSON syntax is
important.

---

### 🛠️ General editing tips

- Update the corresponding index file (`items.json`, `creatures.json`, etc.)
  when adding or removing an entry.
- Path references are relative to their parent module (e.g. `weapon/sword_iron`).
- JSON is permissive but care should be taken with commas and value types; the
  server parser performs minimal validation.
- Use the editor project or scripts (TBD) for bulk generation/balancing.
