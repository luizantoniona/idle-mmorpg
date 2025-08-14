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
