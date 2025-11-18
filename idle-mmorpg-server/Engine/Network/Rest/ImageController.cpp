#include "ImageController.h"

#include <Engine/Manager/Configuration/ServerImageManager.h>
#include <Shared/Commons/Singleton.h>

namespace Network {

void ImageController::image( const drogon::HttpRequestPtr& request, std::function<void( const drogon::HttpResponsePtr& )>&& callback, std::string name ) const {
    auto& imageManager = Commons::Singleton<Engine::ServerImageManager>::instance();

    const auto* imageBuffer = imageManager.imageById( name );
    if ( !imageBuffer ) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode( drogon::k404NotFound );
        resp->setBody( "Image not found: " + name );
        callback( resp );
        return;
    }

    std::string contentType = "application/octet-stream";

    size_t dot = name.rfind( '.' );
    if ( dot != std::string::npos ) {
        std::string ext = name.substr( dot + 1 );
        std::transform( ext.begin(), ext.end(), ext.begin(), ::tolower );

        if ( ext == "png" ) {
            contentType = "image/png";

        } else if ( ext == "jpg" ) {
            contentType = "image/jpeg";

        } else if ( ext == "jpeg" ) {
            contentType = "image/jpeg";

        } else if ( ext == "gif" ) {
            contentType = "image/gif";
        }
    }

    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode( drogon::k200OK );
    resp->setContentTypeString( contentType );

    resp->setBody( std::string( imageBuffer->begin(), imageBuffer->end() ) );

    callback( resp );
}

} // namespace Network
