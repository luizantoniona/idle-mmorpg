# ⚙️ idle-mmorpg-configuration

Global configuration values used by the server. This file is read at startup and
may affect game pace and presentation.

## Structure

- `configuration.json` – single JSON object containing key parameters.
- `logo/` – optional assets referenced by configuration (the current logo image
  is not interpreted by the server but used by documentation and clients).

## Configuration fields

```json
{
  "tickRate": 20,
  "logo": "logo/logo.png",
  "experience": {
    "baseExperience": 100,
    "growthRate": 1.05
  }
}
```

- `tickRate` – server update frequency in ticks per second.
- `logo` – path to logo asset (relative to the configuration package root).
- `experience` – object with experience curve settings:
  - `baseExperience` – starting value for XP awards.
  - `growthRate` – multiplicative factor per level or stage.

### Editing tips

- Changing values requires a server restart to take effect.
- Values here are often exposed to configuration UIs; keep them within
  reasonable ranges to avoid destabilizing progression.
- Additional fields may be added as features demand; the server ignores
  unknown keys.

This package currently only holds a few tuning parameters but may grow
over time to include rate settings, debug flags, or other global constants.
