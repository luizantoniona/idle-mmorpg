#include <drogon/drogon.h>

#include <Engine/Manager/Creature/CreatureManager.h>
#include <Engine/Manager/Denizen/DenizenManager.h>
#include <Engine/Manager/Item/ItemManager.h>
#include <Engine/Manager/Skill/SkillManager.h>
#include <Engine/Manager/Spell/SpellManager.h>
#include <Engine/Manager/World/WorldManager.h>
#include <Infrastructure/Database/Database.h>
#include <Shared/Commons/Singleton.h>

namespace {
// TODO See how to deploy
constexpr const char* DATABASE_PATH = "../../../database/server_data";

constexpr const char* ITEM_DATA_PATH = "../../../idle-mmorpg-data/idle-mmorpg-item/";
constexpr const char* SKILL_DATA_PATH = "../../../idle-mmorpg-data/idle-mmorpg-skill/";
constexpr const char* SPELL_DATA_PATH = "../../../idle-mmorpg-data/idle-mmorpg-spell/";

constexpr const char* CREATURE_DATA_PATH = "../../../idle-mmorpg-data/idle-mmorpg-creature/";
constexpr const char* DENIZEN_DATA_PATH = "../../../idle-mmorpg-data/idle-mmorpg-denizen/";
constexpr const char* WORLD_DATA_PATH = "../../../idle-mmorpg-data/idle-mmorpg-world/";
} // namespace

int main() {
    std::cout << "Starting Server" << std::endl;

    Commons::Singleton<Database::Database>::instance().initialize( DATABASE_PATH );

    Commons::Singleton<Engine::ItemManager>::instance().initialize( ITEM_DATA_PATH );
    Commons::Singleton<Engine::SkillManager>::instance().initialize( SKILL_DATA_PATH );
    Commons::Singleton<Engine::SpellManager>::instance().initialize( SPELL_DATA_PATH );

    Commons::Singleton<Engine::CreatureManager>::instance().initialize( CREATURE_DATA_PATH );
    Commons::Singleton<Engine::DenizenManager>::instance().initialize( DENIZEN_DATA_PATH );
    Commons::Singleton<Engine::WorldManager>::instance().initialize( WORLD_DATA_PATH );

    drogon::app().addListener( "0.0.0.0", 8080 ).setThreadNum( std::thread::hardware_concurrency() ).registerPostHandlingAdvice( []( const drogon::HttpRequestPtr& request, const drogon::HttpResponsePtr& response ) {
                                                                                                        response->addHeader( "Access-Control-Allow-Origin", "*" );
                                                                                                        response->addHeader( "Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS" );
                                                                                                        response->addHeader( "Access-Control-Allow-Headers", "Content-Type, Authorization" );
                                                                                                    } )
        .run();

    std::cout << "Ending Server" << std::endl;

    return 0;
}
