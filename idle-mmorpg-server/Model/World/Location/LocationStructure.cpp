#include "LocationStructure.h"

namespace {
constexpr const char* JSON_ID = "id";
constexpr const char* JSON_LABEL = "label";
constexpr const char* JSON_DESCRIPTION = "description";
} // namespace

namespace Model {

LocationStructure::LocationStructure() :
    _id( "" ),
    _label( "" ),
    _description( "" ) {}

Json::Value LocationStructure::toJson() const {
    Json::Value root;
    root[ JSON_ID ] = id();
    root[ JSON_LABEL ] = label();
    root[ JSON_DESCRIPTION ] = description();
    return root;
}

std::string LocationStructure::id() const {
    return _id;
}

void LocationStructure::setId( const std::string& id ) {
    _id = id;
}

std::string LocationStructure::label() const {
    return _label;
}

void LocationStructure::setLabel( const std::string& label ) {
    _label = label;
}

std::string LocationStructure::description() const {
    return _description;
}

void LocationStructure::setDescription( const std::string& description ) {
    _description = description;
}

} // namespace Model
