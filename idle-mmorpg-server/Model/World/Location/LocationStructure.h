#ifndef LOCATIONSTRUCTURE_H
#define LOCATIONSTRUCTURE_H

#include <string>

#include <json/json.h>

namespace Model {

class LocationStructure {
public:
    LocationStructure();

    Json::Value toJson() const;

    std::string id() const;
    void setId( const std::string& id );

    std::string label() const;
    void setLabel( const std::string& label );

    std::string description() const;
    void setDescription( const std::string& description );

private:
    std::string _id;
    std::string _label;
    std::string _description;
};

} // namespace Model

#endif // LOCATIONSTRUCTURE_H
