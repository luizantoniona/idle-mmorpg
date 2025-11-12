#include "Repository.h"

#include <Commons/Singleton.h>
#include <Database/Database.h>

namespace Repository {

Repository::Repository() :
    _db( Commons::Singleton<Database::Database>::instance().database() ) {}

} // namespace Repository
