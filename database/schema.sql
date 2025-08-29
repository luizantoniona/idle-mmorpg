CREATE TABLE user (
    id_user INTEGER PRIMARY KEY AUTOINCREMENT,
    ds_username VARCHAR,
    ds_password VARCHAR
);

CREATE TABLE 'character' (
    id_character INTEGER PRIMARY KEY AUTOINCREMENT,
    id_user INTEGER NOT NULL,
    ds_name VARCHAR(20) NOT NULL,

    FOREIGN KEY (id_user) REFERENCES user(id_user) ON DELETE CASCADE
);

CREATE TABLE character_attributes (
    id_character INTEGER PRIMARY KEY,
    strength NUMERIC DEFAULT 0.0,
    dexterity NUMERIC DEFAULT 0.0,
    constitution NUMERIC DEFAULT 0.0,
    intelligence NUMERIC DEFAULT 0.0,
    wisdom NUMERIC DEFAULT 0.0,

    FOREIGN KEY (id_character) REFERENCES 'character'(id_character) ON DELETE CASCADE
);

CREATE TABLE character_combat_attributes (
    id_character INTEGER PRIMARY KEY,
    attack NUMERIC DEFAULT 0.0,
    accuracy NUMERIC DEFAULT 0.0,
    defense NUMERIC DEFAULT 0.0,
    speed NUMERIC DEFAULT 0.0,
    critical_chance NUMERIC DEFAULT 0.0,
    critical_multiplier NUMERIC DEFAULT 1.0,

    FOREIGN KEY (id_character) REFERENCES 'character'(id_character) ON DELETE CASCADE
);

CREATE TABLE character_coordinates (
    id_character INTEGER PRIMARY KEY,
    location_id TEXT,
    structure_id TEXT,
    spawn_location_id TEXT,
    spawn_structure_id TEXT,

    FOREIGN KEY (id_character) REFERENCES 'character'(id_character) ON DELETE CASCADE
);

CREATE TABLE character_equipment (
    id_character INTEGER PRIMARY KEY,
    helmet_item_id TEXT DEFAULT NULL,
    armor_item_id TEXT DEFAULT NULL,
    leg_item_id TEXT DEFAULT NULL,
    boot_item_id TEXT DEFAULT NULL,
    glove_item_id TEXT DEFAULT NULL,
    left_hand_item_id TEXT DEFAULT NULL,
    right_hand_item_id TEXT DEFAULT NULL,
    amulet_item_id TEXT DEFAULT NULL,
    ring_item_id TEXT DEFAULT NULL,
    pickaxe_item_id TEXT DEFAULT NULL,
    woodaxe_item_id TEXT DEFAULT NULL,
    fishingrod_item_id TEXT DEFAULT NULL,
    shovel_item_id TEXT DEFAULT NULL,
    sickle_item_id TEXT DEFAULT NULL,
    rope_item_id TEXT DEFAULT NULL,

    FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
);

CREATE TABLE character_inventory (
    id_character INTEGER NOT NULL,
    id_item TEXT NOT NULL,
    amount INTEGER DEFAULT 0,

    PRIMARY KEY (id_character, id_item),
    FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
);

CREATE TABLE character_progression (
    id_character INTEGER PRIMARY KEY,
    'level' INTEGER NOT NULL DEFAULT 0,
    experience INTEGER NOT NULL DEFAULT 0,

    FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
);

CREATE TABLE character_quests (
    id_character INTEGER NOT NULL,
    id_quest TEXT NOT NULL,
    type TEXT NOT NULL,
    objective_id TEXT,
    current_amount INTEGER DEFAULT 0,
    objective_amount INTEGER DEFAULT 0,
    finished INTEGER DEFAULT 0,
    claimed INTEGER DEFAULT 0,

    PRIMARY KEY (id_character, id_quest),
    FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
);

CREATE TABLE character_skills (
    id_character INTEGER NOT NULL,
    id_skill TEXT NOT NULL,
    experience INTEGER DEFAULT 0,
    level INTEGER DEFAULT 0,

    PRIMARY KEY (id_character, id_skill),
    FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
);

CREATE TABLE character_spells (
    id_character INTEGER NOT NULL,
    id_spell TEXT NOT NULL,

    PRIMARY KEY (id_character, id_spell),
    FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
); 

CREATE TABLE character_vitals (
    id_character INTEGER PRIMARY KEY,
    health NUMERIC DEFAULT 0.0,
    max_health NUMERIC DEFAULT 0.0,
    base_health_regen NUMERIC DEFAULT 0.0,
    mana NUMERIC DEFAULT 0.0,
    max_mana NUMERIC DEFAULT 0.0,
    base_mana_regen NUMERIC DEFAULT 0.0,
    stamina NUMERIC DEFAULT 0.0,
    max_stamina NUMERIC DEFAULT 0.0,
    base_stamina_regen NUMERIC DEFAULT 0.0,

    FOREIGN KEY (id_character) REFERENCES 'character'(id_character) ON DELETE CASCADE
);

CREATE TABLE character_wallet (
    id_character INTEGER PRIMARY KEY,
    copper INTEGER DEFAULT 0,
    silver INTEGER DEFAULT 0,
    gold INTEGER DEFAULT 0,

    FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
);
