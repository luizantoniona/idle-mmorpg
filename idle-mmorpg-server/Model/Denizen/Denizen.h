#ifndef DENIZEN_H
#define DENIZEN_H

#include <string>

#include <json/json.h>

namespace Model {

class Denizen {
public:
    Denizen();

private:
    std::string _id;
    std::string _name;
    std::string _description;
    std::string _icon;
};

} // namespace Model

#endif // DENIZEN_H
