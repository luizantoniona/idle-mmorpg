#include <drogon/drogon.h>

#include <Infrastructure/Database/Database.h>
#include <Manager/Creature/CreatureManager.h>
#include <Manager/Item/ItemManager.h>
#include <Manager/Skill/SkillManager.h>
#include <Manager/Spell/SpellManager.h>
#include <Manager/World/WorldManager.h>
#include <Shared/Commons/Singleton.h>

namespace {
// TODO See how to deploy
constexpr const char* DATABASE_PATH = "../../../database/server_data";
constexpr const char* ITEM_DATA_PATH = "../../../idle-mmorpg-data/idle-mmorpg-item/";
constexpr const char* CREATURE_DATA_PATH = "../../../idle-mmorpg-data/idle-mmorpg-creature/";
constexpr const char* SKILL_DATA_PATH = "../../../idle-mmorpg-data/idle-mmorpg-skill/";
constexpr const char* SPELL_DATA_PATH = "../../../idle-mmorpg-data/idle-mmorpg-spell/";
constexpr const char* WORLD_DATA_PATH = "../../../idle-mmorpg-data/idle-mmorpg-world/";
} // namespace

int main() {
    std::cout << "Starting Server" << std::endl;

    // --- Database ---
    Commons::Singleton<Database::Database>::instance().initialize( DATABASE_PATH );

    // --- Items ---
    Commons::Singleton<Manager::ItemManager>::instance().initialize( ITEM_DATA_PATH );

    // --- Creatures ---
    Commons::Singleton<Manager::CreatureManager>::instance().initialize( CREATURE_DATA_PATH );

    // --- Skills ---
    Commons::Singleton<Manager::SkillManager>::instance().initialize( SKILL_DATA_PATH );

    // --- Spells ---
    Commons::Singleton<Manager::SpellManager>::instance().initialize( SPELL_DATA_PATH );

    // --- World ---
    Commons::Singleton<Manager::WorldManager>::instance().initialize( WORLD_DATA_PATH );

    drogon::app()
        .addListener( "0.0.0.0", 8080 )
        .setThreadNum( std::thread::hardware_concurrency() )
        .registerPostHandlingAdvice( []( const drogon::HttpRequestPtr& request, const drogon::HttpResponsePtr& response ) {
            response->addHeader( "Access-Control-Allow-Origin", "*" );
            response->addHeader( "Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS" );
            response->addHeader( "Access-Control-Allow-Headers", "Content-Type, Authorization" );
        } )
        .run();

    std::cout << "Ending Server" << std::endl;

    return 0;
}
