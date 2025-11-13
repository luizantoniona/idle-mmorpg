#include "StatusController.h"

namespace Network {

void StatusController::status( const drogon::HttpRequestPtr& request, std::function<void( const drogon::HttpResponsePtr& )>&& callback ) const {
    Json::Value responseJson;

    responseJson[ "message" ] = "Server Active";
    auto resp = drogon::HttpResponse::newHttpJsonResponse( responseJson );
    resp->setStatusCode( drogon::k200OK );
    callback( resp );
}

} // namespace Network
