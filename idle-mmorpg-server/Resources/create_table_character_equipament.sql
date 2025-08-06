CREATE TABLE character_equipment (
    id_character INTEGER PRIMARY KEY,
    head_item_id TEXT,
    chest_item_id TEXT,
    legs_item_id TEXT,
    boots_item_id TEXT,
    gloves_item_id TEXT,
    left_hand_item_id TEXT,
    right_hand_item_id TEXT,
    amulet_item_id TEXT,
    ring_item_id TEXT,
    FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
);
