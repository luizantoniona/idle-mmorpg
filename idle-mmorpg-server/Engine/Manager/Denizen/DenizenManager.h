#ifndef DENIZENMANAGER_H
#define DENIZENMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Domain/Denizen/Denizen.h>

namespace Engine {

class DenizenManager {
public:
    DenizenManager();

    void initialize( const std::string& denizensPath );

    const Domain::Denizen* denizenById( const std::string& idDenizen ) const;

private:
    std::unordered_map<std::string, std::unique_ptr<Domain::Denizen> > _denizens;
};

} // namespace Engine

#endif // DENIZENMANAGER_H
