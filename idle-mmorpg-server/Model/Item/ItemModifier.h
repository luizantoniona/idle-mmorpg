#ifndef ITEMMODIFIER_H
#define ITEMMODIFIER_H

#include <string>

#include <json/json.h>

namespace Model {

class ItemModifier {
public:
    ItemModifier();

    Json::Value toJson();

    std::string type() const;
    void setType( const std::string& type );

    std::string id() const;
    void setId( const std::string& id );

    double value() const;
    void setValue( double value );

private:
    std::string _type;
    std::string _id;
    double _value;
};

} // namespace Model

#endif // ITEMMODIFIER_H
