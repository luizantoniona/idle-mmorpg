CREATE TABLE character_progression (
    id_character INTEGER PRIMARY KEY,
    'level' INTEGER NOT NULL DEFAULT 0,
    experience INTEGER NOT NULL DEFAULT 0,

    FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
);
