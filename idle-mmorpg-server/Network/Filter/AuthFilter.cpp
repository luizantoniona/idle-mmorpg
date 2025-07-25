#include "AuthFilter.h"

#include <Commons/Singleton.h>
#include <Network/NetworkServer.h>
#include <Network/NetworkSession.h>

namespace Network {

void AuthFilter::doFilter( const drogon::HttpRequestPtr& request, drogon::FilterCallback&& callback, drogon::FilterChainCallback&& chainCallback ) {
    if ( request->method() == drogon::HttpMethod::Options ) {
        chainCallback();
        return;
    }

    auto token = request->getHeader( "Authorization" );
    const std::string prefix = "X-Session ";

    if ( token.rfind( prefix, 0 ) == 0 ) {
        std::string sessionId = token.substr( prefix.length() );

        std::optional<NetworkSession> session = Commons::Singleton<NetworkServer>::instance().getSession( sessionId );
        if ( session ) {
            chainCallback();
            return;
        }
    }

    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode( drogon::k401Unauthorized );
    res->setBody( "Unauthorized" );
    callback( res );
}

} // namespace Network
