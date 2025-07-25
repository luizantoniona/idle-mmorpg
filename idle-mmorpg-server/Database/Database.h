#ifndef DATABASE_H
#define DATABASE_H

#include <string>

#include <sqlite3.h>

namespace Database {

class Database {
public:
    Database();
    ~Database();

    bool create();
    bool migrate();
    bool initialize( const std::string& databasePath );

    sqlite3* database();

private:
    sqlite3* _database;
    std::string _databasePath;

    bool open();
    void close();
};

} // namespace Database

#endif // DATABASE_H
