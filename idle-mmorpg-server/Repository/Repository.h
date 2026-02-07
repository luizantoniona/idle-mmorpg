#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <sqlite3.h>

namespace Repository {

class Repository {
public:
    explicit Repository();

protected:
    sqlite3* _db;
};

} // namespace Repository

#endif // REPOSITORY_H
