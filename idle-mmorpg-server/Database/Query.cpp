#include "Query.h"

#include <stdexcept>

namespace Database {

Query::Query( sqlite3* db, const std::string& sql ) :
    _stmt( nullptr ) {
    if ( sqlite3_prepare_v2( db, sql.c_str(), -1, &_stmt, nullptr ) != SQLITE_OK ) {
        throw std::runtime_error( "Failed to prepare statement: " + std::string( sqlite3_errmsg( db ) ) );
    }
}

Query::~Query() {
    if ( _stmt ) {
        sqlite3_finalize( _stmt );
    }
}

bool Query::step() {
    int result = sqlite3_step( _stmt );
    return result == SQLITE_ROW;
}

bool Query::exec() {
    int result = sqlite3_step( _stmt );
    return result == SQLITE_DONE;
}

void Query::reset() {
    sqlite3_reset( _stmt );
    sqlite3_clear_bindings( _stmt );
}

bool Query::bindInt( int index, int value ) {
    return sqlite3_bind_int( _stmt, index, value ) == SQLITE_OK;
}

bool Query::bindDouble( int index, double value ) {
    return sqlite3_bind_double( _stmt, index, value ) == SQLITE_OK;
}

bool Query::bindText( int index, const std::string& value ) {
    return sqlite3_bind_text( _stmt, index, value.c_str(), -1, SQLITE_TRANSIENT ) == SQLITE_OK;
}

int Query::getColumnInt( int index ) {
    return sqlite3_column_int( _stmt, index );
}

double Query::getColumnDouble( int index ) {
    return sqlite3_column_double( _stmt, index );
}

std::string Query::getColumnText( int index ) {
    const unsigned char* text = sqlite3_column_text( _stmt, index );
    return text ? reinterpret_cast<const char*>( text ) : "";
}

} // namespace Database
