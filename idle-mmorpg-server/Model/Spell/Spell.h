#ifndef SPELL_H
#define SPELL_H

#include <string>

#include "SpellEffect.h"

namespace Model {

class Spell {
public:
    Spell();

    std::string id() const;
    void setId( const std::string& id );

    std::string name() const;
    void setName( const std::string& name );

    std::string description() const;
    void setDescription( const std::string& description );

    std::string icon() const;
    void setIcon( const std::string& icon );

    std::string type() const;
    void setType( const std::string& type );

    int manaCost() const;
    void setManaCost( int manaCost );

    int cooldown() const;
    void setCooldown( int cooldown );

    SpellEffect& effect();
    void setEffect( const SpellEffect& effect );

private:
    std::string _id;
    std::string _name;
    std::string _description;
    std::string _icon;
    std::string _type;
    int _manaCost;
    int _cooldown;
    SpellEffect _effect;
};

} // namespace Model

#endif // SPELL_H
