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
