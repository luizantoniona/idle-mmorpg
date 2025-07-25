#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <drogon/HttpController.h>

#include <Network/Filter/AuthFilter.h>

namespace Network {

class AuthController : public drogon::HttpController<AuthController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO( AuthController::login, "/login", drogon::Post, drogon::Options );
    ADD_METHOD_TO( AuthController::logout, "/logout", drogon::Post, drogon::Options, "Network::AuthFilter" );
    ADD_METHOD_TO( AuthController::sign, "/sign", drogon::Post );
    METHOD_LIST_END

    void login( const drogon::HttpRequestPtr& request, std::function<void( const drogon::HttpResponsePtr& )>&& callback ) const;

    void logout( const drogon::HttpRequestPtr& request, std::function<void( const drogon::HttpResponsePtr& )>&& callback ) const;

    void sign( const drogon::HttpRequestPtr& request, std::function<void( const drogon::HttpResponsePtr& )>&& callback ) const;
};

} // namespace Network

#endif // AUTHCONTROLLER_H
