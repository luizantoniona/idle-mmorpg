#include "Database.h"

#include <iostream>

namespace Database {

Database::Database() :
    _database( nullptr ),
    _databasePath( "" ) {}

Database::~Database() {
    close();
}

bool Database::create() {
    if ( !open() ) {
        return false;
    }

    return true;
}

bool Database::migrate() {
    if ( !open() ) {
        return false;
    }

    char* errorMsg = nullptr;

    const char* MIGRATION_TABLE_SQL = R"SQL(
        CREATE TABLE IF NOT EXISTS schema_migrations (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            executed DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    )SQL";

    if ( sqlite3_exec( _database, MIGRATION_TABLE_SQL, nullptr, nullptr, &errorMsg ) != SQLITE_OK ) {
        std::cerr << "[Database][migrate] " << errorMsg << std::endl;
        sqlite3_free( errorMsg );
        return false;
    }

    // TODO: FUTURAMENTE Execute os SQL's migrations caso não tenha rodado

    return true;
}

bool Database::initialize( const std::string& databasePath ) {
    _databasePath = databasePath;
    return open() && create() && migrate();
}

sqlite3* Database::database() {
    return _database;
}

bool Database::open() {
    if ( _database != nullptr ) {
        return true;
    }

    int returnCode = sqlite3_open( _databasePath.c_str(), &_database );
    if ( returnCode ) {
        std::cerr << "[Database][open]" << sqlite3_errmsg( _database ) << std::endl;
        _database = nullptr;
        return false;
    }

    sqlite3_exec( _database, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr );

    return true;
}

void Database::close() {
    if ( _database != nullptr ) {
        sqlite3_close( _database );
        _database = nullptr;
    }
}

} // namespace Database
