#ifndef DENIZENFACTORY_H
#define DENIZENFACTORY_H

#include <memory>
#include <unordered_map>

#include <Domain/Denizen/Denizen.h>

namespace Engine {

class DenizenFactory {
public:
    static std::unordered_map<std::string, std::unique_ptr<Domain::Denizen> > createDenizens( const std::string& denizensPath );

private:
    static std::unique_ptr<Domain::Denizen> createDenizen( const std::string& denizenPath );
};

} // namespace Engine

#endif // DENIZENFACTORY_H
