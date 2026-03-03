# 📘 Character Event Bus

This document describes the **internal communication mechanism** used by a
`CharacterInstance` to propagate state changes between its sub‑systems. The
pattern is intentionally lightweight and built around two simple concepts:

- **CharacterEventType** – an `enum` representing the different kinds of events.
- **CharacterEvent** – a small object that pairs a type with a `Json::Value` payload.

A single shared `CharacterEventBus` object is owned by `CharacterInstance` and
is passed to each controller when it is constructed. Controllers publish events
when something noteworthy happens (loot gained, skill leveled, vitals changed,
etc.) and other controllers subscribe to the types they care about.

Because the payload is a JSON value, the structure is deliberately untyped; the
following section documents the expected fields for each event.

---

## Event types & payload requirements

| Event                           | Description                                        | Payload fields |
|---------------------------------|----------------------------------------------------|----------------|
| `EQUIPMENT_ITEM_EQUIPPED`       | Equipment was (re)resolved on entry to world       | none (`{}`)    |
| `INVENTORY_ITEM_GAINED`         | Item added to inventory                            | `item`: string<br>`amount`: int |
| `PROGRESSION_EXPERIENCE_GAINED` | General progression XP awarded                     | `value`: int   |
| `PROGRESSION_LEVEL_GAINED`      | General progression Level up                       | none (`{}`)    |
| `SKILL_EXPERIENCE_GAINED`       | XP gained for a particular skill                   | `skill`: int (*Domain::SkillType*)<br>`experience`: int |
| `SKILL_LEVEL_GAINED`            | Level gained for a particular skill                | `skill`: int (*Domain::SkillType*)|
| `VITAL_MAX_HEALTH_GAINED`       | Max health increased                               | `value`: double |
| `VITAL_MAX_MANA_GAINED`         | Max mana increased                                 | `value`: double |
| `VITAL_MAX_STAMINA_GAINED`      | Max stamina increased                              | `value`: double |
| `VITAL_HEALTH_CHANGED`          | Current health changed (pos/neg)                   | `value`: double |
| `VITAL_MANA_CHANGED`            | Current mana changed (pos/neg)                     | `value`: double |
| `VITAL_STAMINA_CHANGED`         | Current stamina changed (pos/neg)                  | `value`: double |
| `WALLET_COIN_GAINED`            | Currency added to wallet                           | `item`: string (`coin_*` )<br>`amount`: int |
| `UNKNOWN`                       | Placeholder / default                              | ignored        |

> **Note:** the types above correspond exactly to the entries in
> `Engine/Instance/Character/EventBus/CharacterEventType.h`.

---

## Architecture overview

1. A `CharacterInstance` is created when a player joins the world.
2. Several controllers (actions, equipment, skills, vitals, etc.) are
   instantiated with a reference to the shared event bus.
3. When a controller observes or triggers a meaningful change it publishes a
   `CharacterEvent` with a JSON payload.
4. Other controllers (or the instance itself) may have previously subscribed to
   the event type and will receive the payload via a callback.
5. Events may also originate from outside the character instance, such as the
   combat system publishing `INVENTORY_ITEM_GAINED` or `VITAL_HEALTH_CHANGED`.

The event bus is merely an in‑process pub/sub; it does **not** cross network
boundaries. WebSocket messages are produced separately by the message sender
controllers using the same underlying character state.

---

## Extending the bus

To add a new event type:

1. Add a value to the `CharacterEventType` enum and bump `UNKNOWN` to the end.
2. Update any publishing code to supply a payload adhering to whatever schema
   you choose.
3. Add a corresponding subscription where the event should be handled.
4. Document the new event in this file so others know what fields are required.

**Publishing example:**

```cpp
Json::Value payload;
payload["value"] = 10.0;
eventBus.publish(CharacterEvent(CharacterEventType::VITAL_MANA_CHANGED, payload));
```

**Subscription example:**

```cpp
_eventBus.subscribe(CharacterEventType::INVENTORY_ITEM_GAINED, [this](const CharacterEvent& e) {
    auto item = e.payload()["item"].asString();
    auto amount = e.payload()["amount"].asInt();
    // ... do something ...
});
```
