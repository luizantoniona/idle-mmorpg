CREATE TABLE character_attributes (
    id_character INTEGER PRIMARY KEY,
    strength NUMERIC DEFAULT 0.0,
    dexterity NUMERIC DEFAULT 0.0,
    constitution NUMERIC DEFAULT 0.0,
    intelligence NUMERIC DEFAULT 0.0,
    wisdom NUMERIC DEFAULT 0.0,
    charisma NUMERIC DEFAULT 0.0,

    FOREIGN KEY (id_character) REFERENCES 'character'(id_character) ON DELETE CASCADE
);
