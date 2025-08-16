CREATE TABLE character_equipment (
    id_character INTEGER PRIMARY KEY,
    helmet_item_id TEXT DEFAULT NULL,
    armor_item_id TEXT DEFAULT NULL,
    leg_item_id TEXT DEFAULT NULL,
    boot_item_id TEXT DEFAULT NULL,
    glove_item_id TEXT DEFAULT NULL,
    left_hand_item_id TEXT DEFAULT NULL,
    right_hand_item_id TEXT DEFAULT NULL,
    amulet_item_id TEXT DEFAULT NULL,
    ring_item_id TEXT DEFAULT NULL,
    pickaxe_item_id TEXT DEFAULT NULL,
    woodaxe_item_id TEXT DEFAULT NULL,
    fishrod_item_id TEXT DEFAULT NULL,
    shovel_item_id TEXT DEFAULT NULL,
    sickle_item_id TEXT DEFAULT NULL,

    FOREIGN KEY (id_character) REFERENCES character(id_character) ON DELETE CASCADE
);
