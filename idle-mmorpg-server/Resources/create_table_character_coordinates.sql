CREATE TABLE character_coordinates (
    id_character INTEGER PRIMARY KEY,
    location_id TEXT,
    structure_id TEXT,
    spawn_location_id TEXT,
    spawn_structure_id TEXT,

    FOREIGN KEY (id_character) REFERENCES 'character'(id_character) ON DELETE CASCADE
);
