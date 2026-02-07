CREATE TABLE character_vitals (
    id_character INTEGER PRIMARY KEY,
    health NUMERIC DEFAULT 0.0,
    max_health NUMERIC DEFAULT 0.0,
    mana NUMERIC DEFAULT 0.0,
    max_mana NUMERIC DEFAULT 0.0,
    stamina NUMERIC DEFAULT 0.0,
    max_stamina NUMERIC DEFAULT 0.0,

    FOREIGN KEY (id_character) REFERENCES 'character'(id_character) ON DELETE CASCADE
);
