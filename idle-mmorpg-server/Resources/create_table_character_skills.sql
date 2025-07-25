CREATE TABLE character_skills (
    id_character INTEGER NOT NULL,
    id_skill TEXT NOT NULL,
    experience INTEGER DEFAULT 0,
    level INTEGER DEFAULT 0,

    PRIMARY KEY (id_character, id_skill),
    FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
);
