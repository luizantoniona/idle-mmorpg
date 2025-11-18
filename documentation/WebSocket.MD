# 📘 WebSocket Documentation

### Overview

This WebSocket server is designed to provide real-time communication between the game client and the server. It allows the client to receive updates about the character, location, combat, and other game systems, and also enables the client to send actions or requests to the server.

All messages are **JSON-encoded**, and each message is categorized by a type (event name) that defines its purpose.

### Key Features:
- Real-time updates for character stats, inventory, equipment, vitals, skills, and progression.
- Real-time updates for location information including NPCs, actions, and connections.
- Combat room management and combat state synchronization.
- Client-driven actions including character actions, structure updates, movement, and combat room management.

## Event Structure

Each WebSocket message follows the general structure:

```json
{
  "type": "EVENT_NAME",
  "payload": { ... }
}
```
- **type**: The name of the event (e.g., CHARACTER_UPDATE).
- **payload**: The data associated with the event.

## Server → Client Events

The server sends events to the client to inform it of changes or updates:

**Character Updates**:  
- CHARACTER_UPDATE
- CHARACTER_DEAD
- CHARACTER_ATTRIBUTES_UPDATE
- CHARACTER_EFFECTS_UPDATE
- CHARACTER_EQUIPMENT_UPDATE
- CHARACTER_INVENTORY_UPDATE
- CHARACTER_PROGRESSION_UPDATE
- CHARACTER_QUESTS_UPDATE
- CHARACTER_SKILLS_UPDATE
- CHARACTER_SPELLS_UPDATE
- CHARACTER_VITALS_UPDATE
- CHARACTER_WALLET_UPDATE

**Character Current State Updates**:
- CHARACTER_CURRENT_ACTION_UPDATE
- CHARACTER_CURRENT_COORDINATES_UPDATE

**Location Updates**:
- LOCATION_UPDATE

**Location Combat Rooms**
- COMBAT_ROOMS_UPDATE
- COMBAT_UPDATE

## Client → Server Events

The client sends events to the server to perform actions or request changes:

**Character Actions**: 
- CHARACTER_ACTION_UPDATE
- CHARACTER_EQUIP_ITEM
- CHARACTER_USE_ITEM
- CHARACTER_CAST_SPELL
- CHARACTER_INTERACT_DENIZEM
- CHARACTER_TRADE_DENIZEN
- CHARACTER_ACCEPT_DENIZEN_QUEST
- CHARACTER_FINISH_DENIZEN_QUEST

**Structure Updates**: 
- CHARACTER_STRUCTURE_UPDATE

**Location Changes**: 
- CHARACTER_LOCATION_UPDATE

**Combat Room Management**: 
- COMBAT_ROOM_CREATE
- COMBAT_ROOM_ENTER
- COMBAT_ROOM_EXIT

# WIP (Work in Progress)