#include "CharacterController.h"

#include <optional>

#include <Commons/Singleton.h>
#include <Repository/Character/CharacterRepository.h>
#include <Database/Database.h>
#include <Network/NetworkServer.h>
#include <Network/NetworkSession.h>

namespace Network {

void CharacterController::create( const drogon::HttpRequestPtr& request, std::function<void( const drogon::HttpResponsePtr& )>&& callback ) const {
    auto token = request->getHeader( "Authorization" );
    const std::string prefix = "X-Session ";

    if ( token.rfind( prefix, 0 ) != 0 ) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode( drogon::k401Unauthorized );
        return callback( resp );
    }

    std::string sessionId = token.substr( prefix.length() );
    std::optional<NetworkSession> session = Commons::Singleton<NetworkServer>::instance().getSession( sessionId );

    if ( !session ) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode( drogon::k401Unauthorized );
        return callback( resp );
    }

    Json::Value body = request->getJsonObject() ? *request->getJsonObject() : Json::Value();

    if ( !body.isMember( "name" ) || !body["name"].isString() ) {
        auto resp = drogon::HttpResponse::newHttpJsonResponse( Json::Value {} );
        resp->setStatusCode( drogon::k400BadRequest );
        return callback( resp );
    }

    const std::string name = body["name"].asString();

    int idUser = session->idUser();

    std::cout << "CharacterController::create" << " [ID] " << idUser << " [NAME] " << name << std::endl;

    int idCharacter = Repository::CharacterRepository().createCharacter( idUser, name );

    if ( idCharacter == 0 ) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode( drogon::k500InternalServerError );
        return callback( resp );
    }

    Json::Value responseJson;
    responseJson["message"] = "Character created";
    responseJson["idCharacter"] = idCharacter;

    auto resp = drogon::HttpResponse::newHttpJsonResponse( responseJson );
    resp->setStatusCode( drogon::k201Created );
    callback( resp );
}

void CharacterController::remove( const drogon::HttpRequestPtr& request, std::function<void (const drogon::HttpResponsePtr&)>&& callback ) const {
    auto token = request->getHeader( "Authorization" );
    const std::string prefix = "X-Session ";

    if ( token.rfind( prefix, 0 ) != 0 ) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode( drogon::k401Unauthorized );
        return callback( resp );
    }

    std::string sessionId = token.substr( prefix.length() );
    std::optional<NetworkSession> session = Commons::Singleton<NetworkServer>::instance().getSession( sessionId );

    if ( !session ) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode( drogon::k401Unauthorized );
        return callback( resp );
    }

    Json::Value body = request->getJsonObject() ? *request->getJsonObject() : Json::Value();

    if ( !body.isMember( "characterId" ) || !body["characterId"].isInt() ) {
        auto resp = drogon::HttpResponse::newHttpJsonResponse( Json::Value {} );
        resp->setStatusCode( drogon::k400BadRequest );
        return callback( resp );
    }

    int idUser = session->idUser();
    int idCharacter = body["characterId"].asInt();

    std::cout << "CharacterController::remove" << " [USER] " << idUser << " [CHARACTER] " << idCharacter << std::endl;

    auto character = Repository::CharacterRepository().findByIdUserAndIdCharacter( idUser, idCharacter );
    if ( !character || character->idUser() != idUser ) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode( drogon::k403Forbidden );
        return callback( resp );
    }

    bool success = Repository::CharacterRepository().deleteCharacter( idCharacter );

    if ( !success ) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode( drogon::k500InternalServerError );
        return callback( resp );
    }

    Json::Value responseJson;
    responseJson["message"] = "Character removed";

    auto resp = drogon::HttpResponse::newHttpJsonResponse( responseJson );
    resp->setStatusCode( drogon::k200OK );
    callback( resp );
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
