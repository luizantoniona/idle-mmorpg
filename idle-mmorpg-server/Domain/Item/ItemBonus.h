#ifndef ITEMBONUS_H
#define ITEMBONUS_H

#include <string>

#include <json/json.h>

namespace Domain {

class ItemBonus {
public:
    ItemBonus();

    Json::Value toJson();

    std::string type() const;
    void setType( const std::string& type );

    std::string category() const;
    void setCategory( const std::string& category );

    double value() const;
    void setValue( double value );

private:
    std::string _type;
    std::string _category;
    double _value;
};

} // namespace Domain

#endif // ITEMBONUS_H
