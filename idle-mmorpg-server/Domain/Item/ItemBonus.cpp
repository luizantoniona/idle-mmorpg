#include "ItemBonus.h"

#include <Domain/Skill/SkillHelper.h>

namespace Domain {

ItemBonus::ItemBonus() :
    _type( SkillType::UNKNOWN ),
    _value( 0.0 ) {}

Json::Value ItemBonus::toJson() const {
    Json::Value root;
    root[ "type" ] = SkillHelper::typeToString( _type );
    root[ "value" ] = _value;
    return root;
}

SkillType ItemBonus::type() const {
    return _type;
}

void ItemBonus::setType( SkillType type ) {
    _type = type;
}

double ItemBonus::value() const {
    return _value;
}

void ItemBonus::setValue( double value ) {
    _value = value;
}

} // namespace Domain
