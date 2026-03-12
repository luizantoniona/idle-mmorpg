#ifndef ITEM_H
#define ITEM_H

#include <string>

#include <json/json.h>

#include <Domain/Skill/SkillType.h>

#include "ItemBonus.h"
#include "ItemCombat.h"
#include "ItemEffect.h"

#include "ItemCategoryType.h"
#include "ItemType.h"

namespace Domain {

class Item {
public:
    Item();

    Json::Value toJson() const;

    std::string id() const;
    void setId( const std::string& id );

    ItemType type() const;
    void setType( ItemType type );

    ItemCategoryType category() const;
    void setCategory( ItemCategoryType category );

    std::string name() const;
    void setName( const std::string& name );

    std::string description() const;
    void setDescription( const std::string& description );

    std::string icon() const;
    void setIcon( const std::string& icon );

    int price() const;
    void setPrice( int price );

    SkillType skill() const;
    void setSkill( SkillType skill );

    ItemBonus bonus() const;
    void setBonus( const ItemBonus& bonus );

    ItemCombat combat() const;
    void setCombat( const ItemCombat& combat );

    ItemEffect effect() const;
    void setEffect( const ItemEffect& effect );

private:
    std::string _id;
    ItemType _type;
    ItemCategoryType _category;
    std::string _name;
    std::string _description;
    std::string _icon;
    int _price;

    SkillType _skill;

    ItemBonus _bonus;
    ItemCombat _combat;
    ItemEffect _effect;
};

} // namespace Domain

#endif // ITEM_H
