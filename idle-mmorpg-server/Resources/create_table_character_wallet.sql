CREATE TABLE character_wallet (
    id_character INTEGER PRIMARY KEY,
    copper INTEGER DEFAULT 0,
    silver INTEGER DEFAULT 0,
    gold INTEGER DEFAULT 0,

FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
);
