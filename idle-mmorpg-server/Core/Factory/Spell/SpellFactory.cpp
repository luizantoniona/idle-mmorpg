#include "SpellFactory.h"

#include <iostream>

#include <Commons/JsonHelper.h>

namespace Core::Factory {

std::unordered_map<std::string, std::unique_ptr<Model::Spell>> SpellFactory::createSpells( const std::string& spellsPath ) {
    std::cout << "SpellFactory::createSpells" << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Model::Spell>> spells;

    Json::Value spellsConfig = Commons::JsonHelper::loadJsonFile( spellsPath + "spells.json" );

    const Json::Value& spellsArray = spellsConfig[ "spells" ];
    for ( const auto& spellEntry : spellsArray ) {
        std::string id = spellEntry[ "id" ].asString();
        std::string fullPath = spellsPath + spellEntry[ "path" ].asString();

        spells[ id ] = createSpell( fullPath );
    }

    std::cout << "SpellFactory::createSpells Number of spells loaded: " << spells.size() << std::endl;

    return spells;
}

std::unique_ptr<Model::Spell> SpellFactory::createSpell( const std::string& spellPath ) {
    std::cout << "SpellFactory::createSpell Spell: " << spellPath << std::endl;

    Json::Value spellJson = Commons::JsonHelper::loadJsonFile( spellPath );

    auto spell = std::make_unique<Model::Spell>();

    spell->setId( spellJson[ "id" ].asString() );
    spell->setName( spellJson[ "name" ].asString() );
    spell->setDescription( spellJson[ "description" ].asString() );
    spell->setIcon( spellJson[ "icon" ].asString() );
    spell->setType( spellJson[ "type" ].asString() );
    spell->setManaCost( spellJson[ "manaCost" ].asInt() );
    spell->setCooldown( spellJson[ "cooldown" ].asInt() );
    spell->effect().setType( spellJson[ "effect" ][ "type" ].asString() );
    spell->effect().setValue( spellJson[ "effect" ][ "value" ].asDouble() );

    return spell;
}

} // namespace Core::Factory
