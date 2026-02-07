CREATE TABLE 'character' (
    id_character INTEGER PRIMARY KEY AUTOINCREMENT,
    id_user INTEGER NOT NULL,
    id_stage INTEGER NOT NULL,
    ds_name VARCHAR(20) NOT NULL,

    FOREIGN KEY (id_user) REFERENCES user(id_user) ON DELETE CASCADE
);
