#include "AuthController.h"

#include <Commons/Singleton.h>
#include <Repository/User/UserRepository.h>
#include <Database/Database.h>
#include <Network/NetworkServer.h>

namespace Network {

void AuthController::login( const drogon::HttpRequestPtr& request, std::function<void( const drogon::HttpResponsePtr& )>&& callback ) const {
    auto requestJson = request->getJsonObject();

    Json::Value responseJson;

    if ( !requestJson ) {
        responseJson[ "error" ] = "No JSON";
        auto response = drogon::HttpResponse::newHttpJsonResponse( responseJson );
        response->setStatusCode( drogon::k400BadRequest );
        callback( response );
        return;
    }

    if ( !requestJson->isMember( "username" ) || !requestJson->isMember( "password" ) ) {
        responseJson[ "error" ] = "Invalid JSON";
        auto response = drogon::HttpResponse::newHttpJsonResponse( responseJson );
        response->setStatusCode( drogon::k400BadRequest );
        callback( response );
        return;
    }

    std::string username = ( *requestJson )[ "username" ].asString();
    std::string password = ( *requestJson )[ "password" ].asString();

    auto user = Repository::UserRepository().findByUsernameAndPassword( username, password );

    if ( !user ) {
        responseJson[ "error" ] = "Invalid credentials";
        auto response = drogon::HttpResponse::newHttpJsonResponse( responseJson );
        response->setStatusCode( drogon::k401Unauthorized );
        callback( response );
        return;
    }

    std::string sessionId = Commons::Singleton<NetworkServer>::instance().createSession( user->idUser(), user->dsUsername() );

    responseJson[ "userID" ] = user->idUser();
    responseJson[ "username" ] = user->dsUsername();
    responseJson[ "sessionID" ] = sessionId;
    responseJson[ "message" ] = "Login successful";

    std::cout << "AuthController::login [User] " << user->dsUsername() << " [UUID] " << sessionId << std::endl;

    auto response = drogon::HttpResponse::newHttpJsonResponse( responseJson );
    response->setStatusCode( drogon::k200OK );
    callback( response );
}

void AuthController::logout( const drogon::HttpRequestPtr& request, std::function<void( const drogon::HttpResponsePtr& )>&& callback ) const {
    auto token = request->getHeader( "Authorization" );
    const std::string prefix = "X-Session ";

    Json::Value responseJson;

    if ( token.rfind( prefix, 0 ) == 0 ) {
        std::string sessionId = token.substr( prefix.length() );
        std::optional<NetworkSession> session = Commons::Singleton<NetworkServer>::instance().getSession( sessionId );

        if ( session && Commons::Singleton<NetworkServer>::instance().deleteSession( sessionId ) ) {

            std::cout << "AuthController::logout" << " [UUID] " << sessionId << std::endl;

            responseJson["message"] = "Logout successful";
            auto response = drogon::HttpResponse::newHttpJsonResponse( responseJson );
            response->setStatusCode( drogon::k200OK );
            callback( response );
            return;

        } else {
            responseJson["error"] = "Failed to destroy session";
            auto response = drogon::HttpResponse::newHttpJsonResponse( responseJson );
            response->setStatusCode( drogon::k500InternalServerError );
            callback( response );
            return;
        }
    }

    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode( drogon::k401Unauthorized );
    callback( resp );
}

void AuthController::sign( const drogon::HttpRequestPtr& request, std::function<void( const drogon::HttpResponsePtr& )>&& callback ) const {
    //TODO Implement sign
}

} // namespace Network
