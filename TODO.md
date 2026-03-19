# 📋 Idle MMORPG - Development Roadmap

### Action System → CharacterActionsController ✅ (PARTIAL)
**Location:** [Engine/Instance/Character/Controller/CharacterActionsController.cpp](idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterActionsController.cpp)

**Status & TODO:**
- ✅ Basic action framework exists (executeCurrentAction, executeTraining)
- ✅ Action selection and validation implemented (handleMessage with CHARACTER_SET_ACTION)
- ✅ Action duration computation with skill-based modifiers (combatSkill method exists)
- ⚠️ **TODO:** Implement gathering action effects (loot drops) - executeCurrentAction has placeholder for TRAIN only
- ⚠️ **TODO:** Implement regenerative action effects - no regenerative logic in executeCurrentAction
- ⚠️ **TODO:** Verify duration calculations match old formula: `base * max(0.5, 1.0 - 0.01 * skillLevel)` - need to check implementation
- [ ] Update to use CharacterEventBus for state changes - no events published
- [ ] Ensure action events are published - missing event publishing

### Regeneration System → CharacterVitalsController ✅ (PARTIAL)
**Location:** [Engine/Instance/Character/Controller/CharacterVitalsController.cpp](idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterVitalsController.cpp)

**Status & TODO:**
- ✅ Health regeneration framework exists (onTick method)
- ✅ Mana regeneration framework exists
- ✅ Stamina regeneration framework exists
- ✅ Regeneration ticks and counters implemented
- ✅ EventBus subscriptions for vital changes exist
- ⚠️ **TODO:** Adjust regeneration formulas; current implementation uses fixed +1 increments rather than configuration values.
- [ ] Integrate skill-based regeneration bonuses - commented out code references vitality/endurance/meditation skills
- [ ] See formula: `baseRegen + (skillLevel * VITAL_SKILL_REGENERATION_MULTIPLIER)`

### Spell System → CharacterSpellsController ✅ (PARTIAL)
**Location:** [Engine/Instance/Character/Controller/CharacterSpellsController.cpp](idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterSpellsController.cpp)

**Status & TODO:**
- ✅ Basic spell controller exists
- ⚠️ **TODO:** Implement spell learning pop-up when unlocking new spells
- [ ] Implement spell cooldown management
- [ ] Add spell learning events to CharacterEventBus
- [ ] Implement spell cast validation (stamina/mana costs)
- [ ] Implement elemental damage system
- [ ] Add spell chain/combo mechanics
- [ ] Create spell enchantment system

### Trade System → (MISSING - Needs NEW TradeController) ❌
**Location:** (Needs to be created: `Engine/Instance/Character/Controller/CharacterTradeController.cpp`)

**Status & TODO:**
- ❌ **NEW:** Create CharacterTradeController
- [ ] Design stage-based NPC data structure
- [ ] Implement trade request validation
- [ ] Implement trade completion logic
- [ ] Add trade events to CharacterEventBus
- [ ] Create WebSocket endpoints for trade

### Chat System (PENDING DECISION)

- **Status:** Needs architectural definition
- **Questions to resolve:**
  - Should peer-to-peer (P2P) communication be used between players?
  - Or should all chat traffic pass through the server?
  - What are the main channels: `GlobalChat`, `StageChat`, `PartyChat`, `DirectMessage`?
  - Should chat messages be persisted in the database?
- **Considerations:**
  - P2P chat reduces server load but requires NAT traversal
  - Server-routed chat allows moderation, filtering, and persistence
  - Different channel types require different architectures
  - Consider anti-spam measures and rate limiting
- **Action Items:**
  - [ ] Design chat protocol specification
  - [ ] Decide on P2P vs server-routed approach
  - [ ] Define channel types and their purposes
  - [ ] Implement chat controller in CharacterInstance
  - [ ] Add chat event types to CharacterEventBus
  - [ ] Create WebSocket chat endpoints

### Server Configuration & Balancing
- **File:** [idle-mmorpg-data/idle-mmorpg-configuration/configuration.json](idle-mmorpg-data/idle-mmorpg-configuration/configuration.json)
- **Status:** Configuration system exists but needs extensive adjustment

**Missing Configuration Values (to be added)**
- [ ] Health regeneration rate (currently hardcoded as 10)
- [ ] Mana regeneration rate (currently hardcoded as 10)
- [ ] Stamina regeneration rate (currently hardcoded as 10)
- [ ] Regeneration tick interval
- [ ] Skill damage scaling multipliers
- [ ] Experience curve adjustments
- [ ] Monster difficulty scaling per stage
- [ ] Item drop rate formulas
- [ ] Stat gain per level-up breakdown (health, mana, stamina, attack, defense)
- [ ] Cooldown durations for spells and abilities
- [ ] Stamina cost per action
- [ ] Resource costs for crafting/training
**Important Items**
- [ ] Create configuration UI in editor
- [ ] Add hot-reload capability for configuration changes

### Deployment & Infrastructure
- **File:** [idle-mmorpg-server/main.cpp](idle-mmorpg-server/main.cpp#L14)
- ⚠️ **TODO:** Implement deployment strategy
- [ ] Create Docker deployment configuration
- [ ] Setup environment variable configuration
- [ ] Implement database migration system
- [ ] Add server logging and monitoring
- [ ] Create CI/CD pipeline
- [ ] Setup error tracking and reporting
- [ ] Implement auto-save mechanism for character data

### Database & Persistence
- **File:** [idle-mmorpg-server/Infrastructure/Database/Database.cpp](idle-mmorpg-server/Infrastructure/Database/Database.cpp#L44)
- ⚠️ **TODO:** Implement SQL migration system (run migrations on startup if not yet executed)
- [ ] Add character save interval
- [ ] Implement transaction system for multi-step operations
- [ ] Create data backup system
- [ ] Add database versioning

## 🌟 Feature Ideas for Idle-MMORPG

### **Guild/Faction System**
- Create player guilds with shared treasury
- Implement guild vs guild warfare/leaderboards
- Add guild perks and technology trees
- Create guild headquarters with upgradeable facilities
- **Implementation Location:** New GuildManager + GuildController

### **Pet/Companion System**
- Allow players to catch/recruit creature companions
- Implement companion battles alongside player
- Add companion skill training and equipment
- Create pet evolution/transformation mechanics
- **Implementation Location:** New CompanionController + Domain/Companion

### **Crafting & Alchemy System**
- Implement crafting recipes across multiple disciplines
- Add gathering → crafting workflow
- Create equipment enhancement/disenchanting
- Implement alchemical potion brewing with effects
- **Implementation Location:** New CraftingController + crafting configuration

### **Dynamic World Events**
- Server-wide events affecting all players
- Invasions requiring collective defense
- King-of-the-hill style PvP events
- World boss encounters with multi-player cooperation
- **Implementation Location:** New WorldEventManager

### **Leaderboard & Rankings**
- Global damage leaderboard
- Stage-completion speed rankings
- Wealth rankings (coin accumulation)
- PvP rating system
- Achievement-based rankings
- **Implementation Location:** New LeaderboardManager + database queries

### **PvP Arena System**
- 1v1 ranked matches
- Team battle modes (3v3, 5v5)
- Battle royale mode
- Seasonal PvP seasons with rankings
- PvP-exclusive items and cosmetics
- **Implementation Location:** New ArenaController + AR endpoints

### **Dungeon/Raid System**
- Multi-floor dungeons with progressive difficulty
- Instanced encounters
- Raid bosses requiring party coordination
- Dungeon weekly lockouts and reset mechanics
- **Implementation Location:** New DungeonController + enhanced StageController

### **Cosmetics && Outfit**
- Implement cosmetic-only items (skins, pets skins, effects)
- Create transmog system for equipment appearance
- Add particle effect customization
- Implement title/badge system
- **Implementation Location:** New CosmeticsController

### **Market/Trade Post**
- Global player-to-player trading system
- Listing management and price history
- Trade tax mechanism
- Price suggestion/market analysis
- **Implementation Location:** New MarketplaceController + database
