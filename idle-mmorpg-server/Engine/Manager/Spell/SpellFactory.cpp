#include "SpellFactory.h"

#include <iostream>

#include <Engine/Manager/Configuration/ServerConfigurationManager.h>
#include <Engine/Manager/Configuration/ServerImageManager.h>
#include <Shared/Commons/Singleton.h>
#include <Shared/Helper/JsonHelper.h>

namespace Engine {

std::unordered_map<std::string, std::unique_ptr<Domain::Spell> > SpellFactory::createSpells( const std::string& spellsPath ) {
    std::cout << "SpellFactory::createSpells" << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Domain::Spell> > spells;

    Json::Value spellsConfig = Helper::JsonHelper::loadJsonFile( spellsPath + "spells.json" );

    for ( const auto& spellEntry : spellsConfig[ "spells" ] ) {
        std::string spellFilePath = spellsPath + spellEntry.asString() + ".json";

        auto spell = createSpell( spellFilePath );
        if ( spell ) {
            spells[ spell->id() ] = std::move( spell );

        } else {
            std::cerr << "Failed to load spell: " << spellFilePath << std::endl;
        }
    }

    std::cout << "SpellFactory::createSpells Number of spells loaded: " << spells.size() << std::endl;

    return spells;
}

std::unique_ptr<Domain::Spell> SpellFactory::createSpell( const std::string& spellPath ) {
    std::cout << "SpellFactory::createSpell Spell: " << spellPath << std::endl;

    Json::Value spellJson = Helper::JsonHelper::loadJsonFile( spellPath );

    auto spell = std::make_unique<Domain::Spell>();

    spell->setId( spellJson[ "id" ].asString() );
    spell->setName( spellJson[ "name" ].asString() );
    spell->setDescription( spellJson[ "description" ].asString() );
    spell->setType( spellJson[ "type" ].asString() );

    spell->setIcon( spellJson[ "icon" ].asString() );
    // TODO: Add image to ServerImageManager

    spell->setManaCost( spellJson[ "manaCost" ].asInt() );
    spell->setCooldown( spellJson[ "cooldown" ].asInt() * Commons::Singleton<Engine::ServerConfigurationManager>::instance().tickRate() );
    spell->effect().setType( spellJson[ "effect" ][ "type" ].asString() );
    spell->effect().setValue( spellJson[ "effect" ][ "value" ].asDouble() );

    return spell;
}

} // namespace Engine
