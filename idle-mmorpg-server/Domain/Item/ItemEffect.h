#ifndef ITEMEFFECT_H
#define ITEMEFFECT_H

#include <json/json.h>

namespace Domain {

class ItemEffect {
public:
    ItemEffect();

    Json::Value toJson() const;

    std::string type() const;
    void setType( const std::string& type );

    std::string category() const;
    void setCategory( const std::string& category );

    double value() const;
    void setValue( double value );

    int duration() const;
    void setDuration( int duration );

private:
    std::string _type;
    std::string _category;
    double _value;
    int _duration;
};

} // namespace Domain

#endif // ITEMEFFECT_H
