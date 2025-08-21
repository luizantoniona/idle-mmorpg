CREATE TABLE character_spells (
    id_character INTEGER NOT NULL,
    id_spell TEXT NOT NULL,

    PRIMARY KEY (id_character, id_spell),
    FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
);
