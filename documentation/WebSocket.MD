# 📘 WebSocket Documentation

### Overview

The WebSocket endpoint (`/ws/character`) is the primary channel for real‑time, bidirectional traffic between client and server. Before opening a socket the client should have a valid session ID obtained via the HTTP API; the token is passed either as an `Authorization: X-Session <id>` header or as the `sid` query parameter. Once the connection is established, every message must follow the JSON envelope described below.

This document lists the supported event types along with general payload guidelines.

All payloads are **JSON-encoded**, and each message is categorized by a type (event name) that defines its purpose.

### Key Features:
- Real-time updates for character stats, inventory, equipment, vitals, skills, and progression.
- Combat room management and combat state synchronization.
- Client-driven actions including character actions and combat room management.

## Event Structure

Each WebSocket message follows the general structure:

```json
{
  "type": "EVENT_NAME",
  "payload": { ... }
}
```

- **type**: The name of the event (e.g., `CHARACTER` or `COMBAT_ROOM_CREATE`). These identifiers correspond to the `MessageSenderType` enum for server‑to‑client events and to `MessageReceiverType` for client‑to‑server messages.
- **payload**: The data associated with the event.

The sections below list the known message types; concrete examples appear at the end of this file.

## Server → Client Events

The server sends events to the client to inform it of changes or updates:

**Character Updates**:  
- CHARACTER
- CHARACTER_ACTIONS
- CHARACTER_EFFECTS
- CHARACTER_EQUIPMENT
- CHARACTER_INVENTORY
- CHARACTER_PROGRESSION
- CHARACTER_SKILLS
- CHARACTER_SPELLS
- CHARACTER_STAGE
- CHARACTER_VITALS
- CHARACTER_WALLET

**Stage Updates**:
- STAGE

**Combat Rooms**
- COMBAT_ROOMS

**Combat**
- COMBAT

## Client → Server Events

The client sends events to the server to perform actions or request changes:

**Character Actions**: 
- CHARACTER_ACTION_SET
- CHARACTER_ITEM_EQUIP
- CHARACTER_ITEM_USE

**Combat Room Management**: 
- COMBAT_ROOM_CREATE
- COMBAT_ROOM_ENTER
- COMBAT_ROOM_EXIT

## Payload examples

### Server → Client

- **CHARACTER** – complete snapshot of the character state (same format returned by the `/characters` API). Example:
```json
{
  "type": "CHARACTER",
  "payload": {
    "id": 1,
    "name": "Zeldar",
    "equipment": { /* ... */ },
    "inventory": [ /* ... */ ],
    "vitals": { "health": 100, "mana": 50, "stamina": 80 },
    /* more fields */
  }
}
```

- **COMBAT_ROOMS** – list of available combat instances:
```json
{
  "type": "COMBAT_ROOMS",
  "payload": {
    "combatInstances": [ { "id": "room1", "participants": 2 }, ... ]
  }
}
```

- **COMBAT** – current combat state when inside a room.

### Client → Server

- **CHARACTER_ACTION_UPDATE** – request to start or change an action:
```json
{
  "type": "CHARACTER_ACTION_SET",
  "payload": {
    "type": 3,
    "optionStage": 2
  }
}
```

- **CHARACTER_ITEM_EQUIP** - request to equip item:
```json
{
  "type": "CHARACTER_ITEM_EQUIP",
  "payload": {
    "item": "iron_sword",
    "slot": "weapon"
  }
}
```

- **CHARACTER_ITEM_USE** - request to use item:
```json
{
  "type": "CHARACTER_ITEM_USE",
  "payload": {
    "item": "food_cheese"
  }
}
```

- **COMBAT_ROOM_CREATE** – payload is an empty object `{}`.

- **COMBAT_ROOM_ENTER** – provide the target room id:
```json
{
  "type": "COMBAT_ROOM_ENTER",
  "payload": { "id": "room1" }
}
```

- **COMBAT_ROOM_EXIT** – simply send `{}`.
