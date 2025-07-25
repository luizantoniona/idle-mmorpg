CREATE TABLE character_coordinates (
    id_character INTEGER PRIMARY KEY,
    x INTEGER DEFAULT 0,
    y INTEGER DEFAULT 0,
    z INTEGER DEFAULT 0,
    x_spawn INTEGER DEFAULT 0,
    y_spawn INTEGER DEFAULT 0,
    z_spawn INTEGER DEFAULT 0,

    FOREIGN KEY (id_character) REFERENCES 'character'(id_character) ON DELETE CASCADE
);
