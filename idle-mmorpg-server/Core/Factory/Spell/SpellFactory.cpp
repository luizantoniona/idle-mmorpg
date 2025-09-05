#include "SpellFactory.h"

#include <iostream>

#include <Commons/JsonHelper.h>
#include <Commons/Singleton.h>
#include <Core/Manager/ServerConfigurationManager.h>

namespace Core::Factory {

std::unordered_map<std::string, std::unique_ptr<Model::Spell> > SpellFactory::createSpells( const std::string& spellsPath ) {
    std::cout << "SpellFactory::createSpells" << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Model::Spell> > spells;

    Json::Value spellsConfig = Commons::JsonHelper::loadJsonFile( spellsPath + "spells.json" );

    for ( const auto& spellEntry : spellsConfig[ "spells" ] ) {
        std::string spellFilePath = spellsPath + spellEntry.asString() + ".json";

        auto spell = createSpell( spellFilePath );
        if ( spell ) {
            spells[spell->id()] = std::move( spell );

        } else {
            std::cerr << "Failed to load spell: " << spellFilePath << std::endl;
        }
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
    spell->setCooldown( spellJson[ "cooldown" ].asInt() * Commons::Singleton<Core::Manager::ServerConfigurationManager>::instance().tickRate() );
    spell->effect().setType( spellJson[ "effect" ][ "type" ].asString() );
    spell->effect().setValue( spellJson[ "effect" ][ "value" ].asDouble() );

    return spell;
}

} // namespace Core::Factory
