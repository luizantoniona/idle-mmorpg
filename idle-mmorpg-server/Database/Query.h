#ifndef QUERY_H
#define QUERY_H

#include <sqlite3.h>
#include <string>

namespace Database {

class Query {
public:
    Query( sqlite3* db, const std::string& sql );
    ~Query();

    bool step();
    void reset();

    bool bindInt( int index, int value );
    bool bindDouble( int index, double value );
    bool bindText( int index, const std::string& value );

    int getColumnInt( int index );
    double getColumnDouble( int index );
    std::string getColumnText( int index );

private:
    sqlite3_stmt* _stmt;
};

} // namespace Database

#endif // QUERY_H
