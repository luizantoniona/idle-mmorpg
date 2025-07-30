#include "CharacterController.h"

#include <optional>

#include <Commons/Singleton.h>
#include <Repository/Character/CharacterRepository.h>
#include <Database/Database.h>
#include <Network/NetworkServer.h>
#include <Network/NetworkSession.h>

namespace Network {

void CharacterController::create( const drogon::HttpRequestPtr& request, std::function<void( const drogon::HttpResponsePtr& )>&& callback ) const {
    //TODO Implement character creation
}

void CharacterController::list( const drogon::HttpRequestPtr& request, std::function<void( const drogon::HttpResponsePtr& )>&& callback ) const {

    auto token = request->getHeader( "Authorization" );
    const std::string prefix = "X-Session ";

    if ( token.rfind( prefix, 0 ) == 0 ) {
        std::string sessionId = token.substr( prefix.length() );
        std::optional<NetworkSession> session = Commons::Singleton<NetworkServer>::instance().getSession( sessionId );

        if ( session ) {
            int idUser = session->idUser();

            Json::Value responseJson;
            Json::Value charactersJson( Json::arrayValue );

            auto characters = Repository::CharacterRepository().findAllByIdUser( idUser );

            for ( const auto& character : characters ) {
                Json::Value characterJson = character->toJson();
                characterJson[ "attributes" ] = character->attributes().toJson();
                characterJson[ "wallet" ] = character->wallet().toJson();
                charactersJson.append( characterJson );
            }

            responseJson[ "characters" ] = charactersJson;
            auto resp = drogon::HttpResponse::newHttpJsonResponse( responseJson );
            resp->setStatusCode( drogon::k200OK );
            return callback( resp );
        }
    }

    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode( drogon::k401Unauthorized );
    callback( resp );
}

} // namespace Network
