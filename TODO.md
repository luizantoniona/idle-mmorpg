# 📋 Idle MMORPG - Development Roadmap

## 🔴 Critical Issues & Bug Fixes

### Character Vitals System (HIGH PRIORITY)
- **File:** [idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterVitalsController.cpp](idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterVitalsController.cpp#L59)
- ⚠️ **TODO:** Tune regeneration amounts and integrate `configurationManager` rates (currently fixed +1 values).
- **Details:** Regeneration logic is implemented with placeholder values. Adjust formulas and apply configuration-based modifiers; the controller already sends updates when vitals change.

### Character Combat & Experience (HIGH PRIORITY)
- **File:** [idle-mmorpg-server/Engine/Instance/Combat/Controller/CombatController.cpp](idle-mmorpg-server/Engine/Instance/Combat/Controller/CombatController.cpp#L33)
- ⚠️ **TODO:** Apply experience to attack weapon skill on dealing damage (line 37)
- **Details:** Combat experience distribution needs proper implementation. Currently these are placeholder TODOs. Combat resolution logic exists but experience events are not published to CharacterEventBus.

## 📦 Legacy System Mapping (OLD → NEW Controllers)

The following systems existed in the OLD architecture and need to be fully implemented in the new CharacterInstance+EventBus architecture:

### 1. Action System → CharacterActionsController ✅ (PARTIAL)
**Old Location:** `Old/ActionSystem.cpp`
**New Location:** [Engine/Instance/Character/Controller/CharacterActionsController.cpp](idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterActionsController.cpp)

**What OLD had:**
- Action selection and validation (changeAction)
- Action duration computation with skill-based modifiers
- Gathering action effects (mining, woodcutting, fishing, herbalism)
- Regenerative action effects (rest, meditate)
- Action counter and completion logic
- Experience distribution per action

**Status & TODO:**
- ✅ Basic action framework exists (executeCurrentAction, executeTraining)
- ✅ Action selection and validation implemented (handleMessage with CHARACTER_SET_ACTION)
- ✅ Action duration computation with skill-based modifiers (combatSkill method exists)
- ⚠️ **TODO:** Implement gathering action effects (loot drops) - executeCurrentAction has placeholder for TRAIN only
- ⚠️ **TODO:** Implement regenerative action effects - no regenerative logic in executeCurrentAction
- ⚠️ **TODO:** Verify duration calculations match old formula: `base * max(0.5, 1.0 - 0.01 * skillLevel)` - need to check implementation
- [ ] Update to use CharacterEventBus for state changes - no events published
- [ ] Ensure action events are published - missing event publishing

### 2. Combat System → CombatController & CombatInstance ✅ (PARTIAL)
**Old Location:** `Old/CombatSystem.cpp`
**New Location:** [Engine/Instance/Combat/Controller/CombatController.cpp](idle-mmorpg-server/Engine/Instance/Combat/Controller/CombatController.cpp)

**What OLD had:**
- Hit damage computation (character → creature)
- Creature counterattack damage calculation
- Spell damage computation
- Hit chance calculations with skill modifiers
- Block/evasion mechanics
- Defense damage reduction
- Experience distribution from combat
- Loot distribution from defeated creatures
- Dynamic multipliers (WEAPON_SKILL_DAMAGE_MULTIPLIER, MAGIC_SKILL_DAMAGE_MULTIPLIER)

**Status & TODO:**
- ✅ Combat resolution exists (resolveCharacterAttack, resolveCreatureAttack)
- ✅ Hit damage computation implemented (character → creature)
- ✅ Creature counterattack damage calculation exists
- ⚠️ **TODO:** Implement spell damage computation - no spell damage logic in CombatController
- ⚠️ **TODO:** Implement block/evasion mechanics - missing in resolveCreatureAttack
- ⚠️ **TODO:** Implement experience skill acquisition from combat - TODOs in code for weapon skill
- [ ] Add combat events to CharacterEventBus (hit, damage taken, spell cast, etc.) - no events published
- [ ] Re-implement damage multipliers from configuration - hardcoded values used

### 4. Regeneration System → CharacterVitalsController ✅ (PARTIAL)
**Old Location:** `Old/RegenerationSystem.cpp`
**New Location:** [Engine/Instance/Character/Controller/CharacterVitalsController.cpp](idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterVitalsController.cpp)

**What OLD had:**
- Health regeneration with vitality skill boost
- Mana regeneration with meditation skill boost
- Stamina regeneration with endurance skill boost
- Regeneration ticks and counters
- Spell cooldown tracking
- Healing spell casting with cooldown reset

**Status & TODO:**
- ✅ Health regeneration framework exists (onTick method)
- ✅ Mana regeneration framework exists
- ✅ Stamina regeneration framework exists
- ✅ Regeneration ticks and counters implemented
- ✅ EventBus subscriptions for vital changes exist
- ⚠️ **TODO:** Adjust regeneration formulas; current implementation uses fixed +1 increments rather than configuration values.
- ⚠️ **TODO:** Implement spell cooldown tracking - not implemented
- ⚠️ **TODO:** Implement healing spell casting - not implemented
- [ ] Integrate skill-based regeneration bonuses - commented out code references vitality/endurance/meditation skills
- [ ] Add regeneration events to CharacterEventBus - events are subscribed to but not published
- [ ] See formula: `baseRegen + (skillLevel * VITAL_SKILL_REGENERATION_MULTIPLIER)`

### 7. Skill System → CharacterSkillsController ✅ (PARTIAL)
**Old Location:** `Old/SkillSystem.h` (header only)
**New Location:** [Engine/Instance/Character/Controller/CharacterSkillsController.cpp](idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterSkillsController.cpp)

**What OLD had:**
- Skill data management and loading

**Status & TODO:**
- ✅ Skill controller framework exists
- ⚠️ **TODO:** Review skill experience logic (global vs per-skill multipliers)
- [ ] Implement skill tree branching (if desired)
- [ ] Add talent point allocation system

### 8. Spell System → CharacterSpellsController ✅ (PARTIAL)
**Old Location:** `Old/SpellSystem.cpp`
**New Location:** [Engine/Instance/Character/Controller/CharacterSpellsController.cpp](idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterSpellsController.cpp)

**What OLD had:**
- Spell learning mechanism
- Spell availability validation

**Status & TODO:**
- ✅ Basic spell controller exists
- ⚠️ **TODO:** Implement spell learning pop-up when unlocking new spells
- [ ] Implement spell cooldown management
- [ ] Add spell learning events to CharacterEventBus

### 9. Trade System → (MISSING - Needs NEW TradeController) ❌
**Old Location:** `Old/TradeSystem.cpp` (DEPRECATED - Used Denizens)
**New Location:** (Needs to be created: `Engine/Instance/Character/Controller/CharacterTradeController.cpp`)

**What OLD had (DEPRECATED):**
- Denizen-based trading (now removed)

**What NEW needs:**
- Stage-based NPC trading
- Trade request/confirmation flow
- Trade inventory management
- Trade completion and item/coin exchange

**Status & TODO:**
- ❌ **NEW:** Create CharacterTradeController
- [ ] Design stage-based NPC data structure
- [ ] Implement trade request validation
- [ ] Implement trade completion logic
- [ ] Add trade events to CharacterEventBus
- [ ] Create WebSocket endpoints for trade

### 10. Training System → CharacterActionsController (Training Action) ✅ (PARTIAL)
**Old Location:** `Old/TrainingSystem.cpp`
**New Location:** [Engine/Instance/Character/Controller/CharacterActionsController.cpp](idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterActionsController.cpp#L27) (executeTraining method exists)

**What OLD had:**
- Skill training action execution
- Skill selection for training
- Experience distribution on training completion

**Status & TODO:**
- ✅ Training action framework exists
- ⚠️ **TODO:** Verify training experience distribution
- [ ] Ensure training respects character skills
- [ ] Add training events to CharacterEventBus

### 11. Effect System → CharacterEffectsController ✅ (PARTIAL)
**Old Location:** `Old/EffectSystem.cpp`
**New Location:** [Engine/Instance/Character/Controller/CharacterEffectsController.cpp](idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterEffectsController.cpp)

**What OLD had:**
- Effect processing and application
- Buff/debuff management (likely)

**Status & TODO:**
- ✅ Effects controller framework exists
- [ ] Implement status effect tracking
- [ ] Implement effect duration management
- [ ] Implement effect modifier calculations
- [ ] Add effect events to CharacterEventBus

---

## 🏗️ Major System Refactors

### 1. Chat System Architecture (PENDING DECISION)
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

### 2. Trade System Refactoring (MAJOR)
- **Current Status:** Trade system is OFFLINE - major refactoring in progress
- **Changes from OLD system:**
  - ❌ Denizens are NO LONGER USED
  - ✅ Trades are NOW STAGE-BASED (tied to specific stages/locations)
  - Each stage can have multiple NPCs with different trade inventories
  - Trades should be part of stage progression mechanics
- **Action Items:**
  - [ ] Design stage-based NPC trading system
  - [ ] Create TradeController within CharacterInstance
  - [ ] Define available trades per stage in world configuration
  - [ ] Implement trade request/confirmation/completion flow
  - [ ] Add trade events to CharacterEventBus
  - [ ] Create trade WebSocket endpoints
  - [ ] Re-enable front-end trade UI components
  - [ ] Add trade history/log to database

### 3. Quest → Stage Objectives System (MAJOR)
- **Current Status:** Quests are being replaced with Stage Objectives
- **Design:**
  - Objectives are tied to stages (not free-roaming)
  - Completing stage objectives unlocks progression to next stage
  - Each new stage brings access to:
    - New actions (gathering, skills)
    - New NPC trades
    - New mob encounters
    - Stage-specific challenges
- **Action Items:**
  - [ ] Design stage progression system
  - [ ] Define objective types (kill count, gather count, exploration, etc.)
  - [ ] Create StageObjectiveController
  - [ ] Implement stage unlock/progression logic
  - [ ] Add objective events to CharacterEventBus
  - [ ] Create WebSocket endpoints for objective tracking
  - [ ] Update front-end to show stage progression UI
  - [ ] Persist stage completion state in database
  - [ ] Design XP/reward scaling per stage difficulty

---

## 🎮 Server Configuration & Balancing

### Currently Incomplete Configuration
- **File:** [idle-mmorpg-data/idle-mmorpg-configuration/configuration.json](idle-mmorpg-data/idle-mmorpg-configuration/configuration.json)
- **Status:** Configuration system exists but needs extensive adjustment

### Missing Configuration Values (to be added)
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

### Action Items
- [x] Create initial configuration framework
- [ ] Extend configuration to support all game parameters
- [ ] Create configuration UI in editor
- [ ] Add hot-reload capability for configuration changes
- [ ] Implement per-stage difficulty modifiers

---

## 🛠️ Systems to Implement / Complete

### Skill System Enhancement
- **File:** [idle-mmorpg-server/Engine/Manager/Skill/SkillFactory.cpp](idle-mmorpg-server/Engine/Manager/Skill/SkillFactory.cpp#L53)
- ⚠️ **TODO:** Review skill experience logic - should be global or per-skill specific values?
- [ ] Implement skill-based damage calculations
- [ ] Create skill combo system
- [ ] Implement skill talent trees
- [ ] Add skill mastery mechanics

### Spell System
- [ ] Implement spell cast validation (stamina/mana costs)
- [ ] Create spell cooldown system
- [ ] Implement elemental damage system
- [ ] Add spell chain/combo mechanics
- [ ] Create spell enchantment system

### Equipment & Upgrades
- [ ] Implement equipment durability system
- [ ] Create equipment upgrade/enhancement mechanics
- [ ] Add socket/gem system (if desired)
- [ ] Implement armor scaling calculations
- [ ] Add equipment set bonuses

### UI & Client Improvements
- **File:** [idle-mmorpg-client/src/app/pages/game/component/panel-character-spells/character-spells.panel.ts](idle-mmorpg-client/src/app/pages/game/component/panel-character-spells/character-spells.panel.ts#L46)
- ⚠️ **TODO:** Implement spell learning popup when unlocking new spells
- **File:** [idle-mmorpg-client/src/app/component/game/item/item.component.ts](idle-mmorpg-client/src/app/component/game/item/item.component.ts#L31)
- ⚠️ **TODO:** Adjust item click handlers and item interaction logic
- [ ] Refine character stat display
- [ ] Implement damage numbers floating text
- [ ] Add combat log UI
- [ ] Create achievement/milestone notifications
- [ ] Implement loading screens between stages

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

---

## 🌟 Feature Ideas for Idle-MMORPG

Based on analysis of the current server architecture, here are promising features to enhance the game:

### 3. **Guild/Faction System**
- Create player guilds with shared treasury
- Implement guild vs guild warfare/leaderboards
- Add guild perks and technology trees
- Create guild headquarters with upgradeable facilities
- **Implementation Location:** New GuildManager + GuildController

### 4. **Pet/Companion System**
- Allow players to catch/recruit creature companions
- Implement companion battles alongside player
- Add companion skill training and equipment
- Create pet evolution/transformation mechanics
- **Implementation Location:** New CompanionController + Domain/Companion

### 5. **Crafting & Alchemy System**
- Implement crafting recipes across multiple disciplines
- Add gathering → crafting workflow
- Create equipment enhancement/disenchanting
- Implement alchemical potion brewing with effects
- **Implementation Location:** New CraftingController + crafting configuration

### 6. **Prestige Skill Trees**
- Multiple skill paths (Warrior, Mage, Ranger, etc.)
- Implement skill point allocation system
- Create skill synergies and combo bonuses
- Add respec mechanics with appropriate costs
- **Implementation Location:** New SkillTreeController

### 7. **Augmentation/Rune System**
- Add rune/augmentation slots to armor and weapons
- Implement rune crafting from gathered materials
- Create rune combination effects
- Add elemental damage variations
- **Implementation Location:** Extend equipment system

### 10. **Dynamic World Events**
- Server-wide events affecting all players
- Invasions requiring collective defense
- King-of-the-hill style PvP events
- World boss encounters with multi-player cooperation
- **Implementation Location:** New WorldEventManager

### 11. **Leaderboard & Rankings**
- Global damage leaderboard
- Stage-completion speed rankings
- Wealth rankings (coin accumulation)
- PvP rating system
- Achievement-based rankings
- **Implementation Location:** New LeaderboardManager + database queries

### 13. **PvP Arena System**
- 1v1 ranked matches
- Team battle modes (3v3, 5v5)
- Battle royale mode
- Seasonal PvP seasons with rankings
- PvP-exclusive items and cosmetics
- **Implementation Location:** New ArenaController + AR endpoints

### 14. **Dungeon/Raid System**
- Multi-floor dungeons with progressive difficulty
- Instanced encounters
- Raid bosses requiring party coordination
- Dungeon weekly lockouts and reset mechanics
- **Implementation Location:** New DungeonController + enhanced StageController

### 16. **Cosmetics**
- Implement cosmetic-only items (skins, pets skins, effects)
- Create transmog system for equipment appearance
- Add particle effect customization
- Implement title/badge system
- **Implementation Location:** New CosmeticsController

### 17. **Daily/Weekly Challenge System**
- Implement daily recurring tasks
- Add weekly special challenges
- Create seasonal objectives
- Automatic reward distribution
- **Implementation Location:** New ChallengeController

### 18. **Market/Trade Post**
- Global player-to-player trading system
- Listing management and price history
- Trade tax mechanism
- Price suggestion/market analysis
- **Implementation Location:** New MarketplaceController + database

### 20. **Enchantment System**
- Refine equipment with rare materials
- Create enchantment leveling progression
- Implement failed enchantment penalties/safeguards
- Add specific enchantment effects per slot
- **Implementation Location:** New EnchantmentController

---

## 🎯 Controller Implementation Status

### Current Controllers (CharacterInstance + EventBus)

#### ✅ Existing Controllers (Need Completion)

| Controller | Status | Needs Implementation | EventBus Integration |
|-----------|--------|----------------------|----------------------|
| CharacterActionsController | Partial | Gathering effects, regenerative effects, action events | Needs events |
| CharacterCombatController | Partial | Attack duration recalculation | Subscribed to equipment events |
| CharacterEffectsController | Basic | Status effects, buffs, debuffs | None |
| CharacterEquipmentController | Partial | Modifier computation, durability | Publishes equipment equipped event |
| CharacterInventoryController | Partial | Item management integration, inventory events | None |
| CharacterProgressionController | Partial | Milestone bonuses, progression events | Subscribed to experience events |
| CharacterSkillsController | Partial | Skill-based calculations, skill events | Subscribed to experience events |
| CharacterSpellsController | Basic | Spell learning popup, cooldown management | None |
| CharacterVitalsController | CRITICAL | Regeneration formulas, spell cooldowns | Subscribed to vital change events |
| CharacterWalletController | Basic | Coin operations | None |
| CombatController | Partial | Spell damage, loot, experience, combat events | None |

#### ❌ Missing Controllers (Need Creation)

| Controller | Purpose | Priority |
|-----------|---------|----------|
| CharacterTradeController | Stage-based NPC trading | HIGH |
| CharacterChatController | Multi-channel chat system | HIGH (pending arch decision) |
| CharacterObjectiveController | Stage objectives & progression | HIGH |
| CharacterCraftingController | Crafting & alchemy | MEDIUM |
| CharacterLeaderboardController | Ranking & statistics tracking | MEDIUM |
| CharacterPvPController | Arena & PvP matchmaking | MEDIUM-LOW |
| CharacterGuildController | Guild membership & perks | MEDIUM-LOW |
| CharacterCompanionController | Pet/companion management | LOW |
