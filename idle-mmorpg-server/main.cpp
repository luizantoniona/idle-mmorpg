#include <drogon/drogon.h>

#include <Commons/Singleton.h>
#include <Core/Manager/CreatureManager.h>
#include <Core/Manager/ItemManager.h>
#include <Core/Manager/SkillManager.h>
#include <Core/Manager/WorldManager.h>
#include <Database/Database.h>

namespace {
// TODO See how to deploy
constexpr const char* DATABASE_PATH = "../../../database/server_data";
constexpr const char* CREATURE_PATH = "../../../idle-mmorpg-data/idle-mmorpg-creature/";
constexpr const char* ITEM_PATH = "../../../idle-mmorpg-data/idle-mmorpg-item/";
constexpr const char* SKILL_PATH = "../../../idle-mmorpg-data/idle-mmorpg-skill/";
constexpr const char* MAP_PATH = "../../../idle-mmorpg-data/idle-mmorpg-map/";
} // namespace

int main() {
    std::cout << "Starting Server" << std::endl;

    Commons::Singleton<Database::Database>::instance().initialize( DATABASE_PATH );
    Commons::Singleton<Core::Manager::ItemManager>::instance().initialize( ITEM_PATH );
    Commons::Singleton<Core::Manager::CreatureManager>::instance().initialize( CREATURE_PATH );
    Commons::Singleton<Core::Manager::SkillManager>::instance().initialize( SKILL_PATH );
    Commons::Singleton<Core::Manager::WorldManager>::instance().initialize( MAP_PATH );

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
