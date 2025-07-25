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
    //TODO Implement logout
}

void AuthController::sign( const drogon::HttpRequestPtr& request, std::function<void( const drogon::HttpResponsePtr& )>&& callback ) const {
    //TODO Implement sign
}

} // namespace Network
