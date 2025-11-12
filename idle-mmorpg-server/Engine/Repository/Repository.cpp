#include "Repository.h"

#include <Infrastructure/Database/Database.h>
#include <Shared/Commons/Singleton.h>

namespace Repository {

Repository::Repository() :
    _db( Commons::Singleton<Database::Database>::instance().database() ) {}

} // namespace Repository
