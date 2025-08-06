CREATE TABLE character_equipment (
    id_character INTEGER PRIMARY KEY,
    head_item_id TEXT DEFAULT NULL,
    chest_item_id TEXT DEFAULT NULL,
    legs_item_id TEXT DEFAULT NULL,
    boots_item_id TEXT DEFAULT NULL,
    gloves_item_id TEXT DEFAULT NULL,
    left_hand_item_id TEXT DEFAULT NULL,
    right_hand_item_id TEXT DEFAULT NULL,
    amulet_item_id TEXT DEFAULT NULL,
    ring_item_id TEXT DEFAULT NULL,
    pickaxe_item_id TEXT DEFAULT NULL,
    woodaxe_item_id TEXT DEFAULT NULL,
    rod_item_id TEXT DEFAULT NULL,
    shovel_item_id TEXT DEFAULT NULL,
    sickle_item_id TEXT DEFAULT NULL,

    FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
);
