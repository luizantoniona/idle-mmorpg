CREATE TABLE character_inventory (
    id_character INTEGER NOT NULL,
    id_item TEXT NOT NULL,
    amount INTEGER DEFAULT 0,

    PRIMARY KEY (id_character, id_item),
    FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
);
