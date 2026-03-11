# 📋 Idle MMORPG - Development Roadmap

## 🔴 Critical Issues & Bug Fixes

### Character Vitals System (HIGH PRIORITY)
- **File:** [idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterVitalsController.cpp](idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterVitalsController.cpp#L59)
- ⚠️ **TODO:** Tune regeneration amounts and integrate `configurationManager` rates (currently fixed +1 values).
- **Details:** Regeneration logic is implemented with placeholder values. Adjust formulas and apply configuration-based modifiers; the controller already sends updates when vitals change.

### Character Combat & Experience (HIGH PRIORITY)
- **File:** [idle-mmorpg-server/Engine/Instance/Combat/Controller/CombatController.cpp](idle-mmorpg-server/Engine/Instance/Combat/Controller/CombatController.cpp#L33)
- ⚠️ **TODO:** Apply experience to endurance skill on damage taken (line 33)
- ⚠️ **TODO:** Apply experience to attack weapon skill on dealing damage (line 37)
- ⚠️ **TODO:** Apply experience to vitality skill on health recovery (line 63)
- **Details:** Combat experience distribution needs proper implementation. Currently these are placeholder TODOs. Combat resolution logic exists but experience events are not published to CharacterEventBus.


### Weapon Attack Duration Recalculation
- **File:** [idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterCombatController.cpp](idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterCombatController.cpp)
- ⚠️ **TODO:** Verify offhand contribution to attack speed when dual-wielding. Weapon-based recalculation is implemented.
- **Details:** Attack duration is now set from weapon attackSpeed, but offhand is not accounted for. Ensure dual-wield logic matches design.
---

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
- ⚠️ **TODO:** Implement experience skill acquisition from combat - TODOs in code for endurance, weapon skill, vitality
- ⚠️ **TODO:** Implement loot computation - computeCharactersLoot exists but incomplete
- [ ] Add combat events to CharacterEventBus (hit, damage taken, spell cast, etc.) - no events published
- [ ] Re-implement damage multipliers from configuration - hardcoded values used

### 3. Progression System → CharacterProgressionController ✅ (PARTIAL)
**Old Location:** `Old/ProgressionSystem.cpp`
**New Location:** [Engine/Instance/Character/Controller/CharacterProgressionController.cpp](idle-mmorpg-server/Engine/Instance/Character/Controller/CharacterProgressionController.cpp)

**What OLD had:**
- Experience point accumulation per skill
- Level-up logic with experience overflow
- Milestone achievements per skill level
- Milestone bonus application (health, mana, stamina gains)
- General character progression XP
- Skill milestone bonuses application

**Status & TODO:**
- ✅ Basic progression framework exists (applyExperience, applyMilestone)
- ✅ Experience point accumulation per skill implemented
- ✅ Level-up logic with experience overflow exists
- ✅ Milestone achievements per skill level implemented
- ✅ Milestone bonus application exists (applyMilestoneBonus)
- ⚠️ **TODO:** Implement milestone detection and bonus application - applyMilestone method exists but may need verification
- ⚠️ **TODO:** Ensure overflow XP is properly carried over on level up - logic exists but needs testing
- [ ] Add progression events to CharacterEventBus - no events published in controller
- [ ] Implement LevelExperienceHelper integration - used in applyExperience
- [ ] Test milestone bonus calculations - hardcoded values in applyLevelUp (line 32,36,40)

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

### 1. **Passive Income Streams** (Core Idle Mechanic)
- Implement "AFK gathering" - characters continue gathering resources when offline
- Add passive skill training during downtime
- Create production facilities (farms, mines) that generate resources over time
- Implement market trading bot for AFK profit
- **Implementation Location:** New PassiveIncomeController in CharacterInstance

### 2. **Prestige/Reincarnation System**
- Allow players to reset character progression for permanent bonuses
- Implement new game+ content with enhanced rewards
- Add prestige shop with unique items/bonuses
- Create achievement milestones that track prestige runs
- **Implementation Location:** New PrestigeController + database tables

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

### 8. **Minigame System**
- Create optional mini-games for resource farming acceleration
- Add gambling/casino mechanics with resource costs
- Implement dungeon runs with time-based challenges
- Create puzzle challenges for bonus rewards
- **Implementation Location:** New MinigameController + separate endpoints

### 9. **Seasonal Events & Battle Pass**
- Implement limited-time seasonal events
- Create battle pass progression system
- Add seasonal exclusive cosmetics and rewards
- Implement rotating stage challenges
- **Implementation Location:** New SeasonalEventController + configuration

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

### 12. **Loot System Enhancement**
- Implement progressive difficulty with scaling loot
- Add rare/epic/legendary item rarities
- Create item affixes and randomization
- Implement loot specialization (class-based rewards)
- Add guaranteed loot thresholds
- **Implementation Location:** Enhance existing LootSystem

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

### 15. **Mentorship/Blessing System**
- Allow veteran players to aid new players
- Implement mentor rewards and recognition
- Create blessing bonuses for mentored players
- Add level sync for scaling content in groups
- **Implementation Location:** New MentorshipController

### 16. **Prestige Cosmetics**
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

### 19. **Prophecy/Prediction System**
- Implement fortune telling mechanics
- Create randomized future rewards
- Add decision trees with outcomes
- Implement cosmic event predictions
- **Implementation Location:** New ProphecyController

### 20. **Enchantment System**
- Refine equipment with rare materials
- Create enchantment leveling progression
- Implement failed enchantment penalties/safeguards
- Add specific enchantment effects per slot
- **Implementation Location:** New EnchantmentController

---

---

## 📊 Priority Matrix

### Immediate (This Sprint)
1. ✅ **LEGACY MIGRATION - Phase 1:**
   - Fix character vitals regeneration system (health, mana, stamina)
   - Implement combat experience distribution to skills
   - Activate gathering action effects
   - Activate regenerative action effects
2. Define chat system architecture (BLOCKING multiple features)
3. Create stage objectives system
4. Create CharacterTradeController for stage-based trades

### Short Term (1-2 Weeks)
1. ✅ **LEGACY MIGRATION - Phase 2:**
   - Complete spell cooling and hotkey management
   - Implement spell damage computation
   - Implement block/evasion mechanics
   - Implement loot generation and distribution
2. Complete trade system refactoring
3. Finalize weapon attack duration calculations
4. Extend server configuration system

### Medium Term (2-4 Weeks)
1. ✅ **LEGACY MIGRATION - Phase 3:**
   - Implement milestone detection and bonus application
   - Skill-based equipment modifier computation
   - Status effect system completion
   - Spell cooldown tracking
2. Implement leaderboard system
3. Create crafting/alchemy system
4. Add prestige/reincarnation mechanics

### Long Term (1+ Month)
1. ✅ **LEGACY MIGRATION - Phase 4:**
   - Review and optimize all completed migrations
   - Full test coverage for all controllers
   - Performance optimization
2. Guild/faction system
3. PvP arena system
4. Dungeon/raid system

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
| CharacterPassiveIncomeController | AFK gathering, passive bonuses | MEDIUM |
| CharacterPrestigeController | Prestige/reincarnation system | MEDIUM |
| CharacterCraftingController | Crafting & alchemy | MEDIUM |
| CharacterMiniGameController | Mini-game participation | MEDIUM |
| CharacterLeaderboardController | Ranking & statistics tracking | MEDIUM |
| CharacterPvPController | Arena & PvP matchmaking | MEDIUM-LOW |
| CharacterGuildController | Guild membership & perks | MEDIUM-LOW |
| CharacterCompanionController | Pet/companion management | LOW |
| CharacterBattlePassController | Season pass progression | LOW |

---

## 📝 Notes

- All TODOs from source code have been documented in the corresponding sections
- **LEGACY MIGRATION:** 11 out of 10 OLD systems partially mapped to 11 controllers; 1 system (Trade) needs complete redesign
- Chat system architecture decision is BLOCKING several dependent features
- Trade and Quest systems are in active refactoring - existing code should not be relied upon
- Configuration system needs significant expansion before proper game balancing
- Server architecture (CharacterInstance + EventBus) is solid foundation for new systems
- **Controller Completion:** Focus should be on completing existing controllers before creating new ones
- **EventBus Integration:** All controllers should publish relevant events for the system to be cohesive

---

## � Controller Code Review Summary (March 4, 2026)

**Review Findings:**
- **Total Controllers Reviewed:** 11 Character controllers + 3 Stage/Combat controllers
- **Controllers with TODOs:** 8 controllers have active TODOs in code
- **EventBus Integration:** 5 controllers have EventBus subscriptions, but only 1 publishes events
- **Critical Gaps:** Regeneration system (CharacterVitalsController) is 90% commented out
- **Best Implemented:** CharacterProgressionController and CharacterSkillsController have most complete logic
- **Most Incomplete:** CharacterEffectsController and CharacterSpellsController lack core functionality

**Key Observations:**
- Controllers follow consistent architecture with onEnterWorld/onTick/handleMessage pattern
- EventBus is underutilized - most state changes don't publish events
- ConfigurationManager integration is missing in many places (hardcoded values)
- Legacy migration is ~60% complete based on OLD system features
- Combat system has solid damage calculation but missing experience/loot distribution

**Immediate Action Items:**
1. Uncomment and fix CharacterVitalsController regeneration (HIGH PRIORITY)
2. Implement CombatController experience distribution
3. Add EventBus event publishing to all controllers
4. Complete CharacterActionsController gathering effects
5. Integrate configuration values instead of hardcoded numbers

---

## �📞 Contact & Questions

For questions about this roadmap, refer to:
- [CharacterEventBus Documentation](documentation/CharacterEventBus.md)
- [API Documentation](documentation/API.md)
- [WebSocket Documentation](documentation/WebSocket.MD)
