#ifndef CHARACTERSPELL_H
#define CHARACTERSPELL_H

#include <string>

#include <json/json.h>

#include <Model/Spell/Spell.h>

namespace Model {

class CharacterSpell {
public:
    CharacterSpell();

    Json::Value toJson() const;

    std::string id() const;
    void setId( const std::string& id );

    int count() const;
    void setCount( int count );

    Spell* spell() const;
    void setSpell( Spell* spell );

    bool isReady();

private:
    std::string _id;
    int _count;
    Spell* _spell;
};

} // namespace Model

#endif // CHARACTERSPELL_H
