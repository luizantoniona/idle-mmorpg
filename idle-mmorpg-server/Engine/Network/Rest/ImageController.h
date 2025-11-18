#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H

#include <drogon/HttpController.h>

namespace Network {

class ImageController : public drogon::HttpController<ImageController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO( ImageController::image, "/image/{name}", drogon::Get, drogon::Options );
    METHOD_LIST_END

    void image( const drogon::HttpRequestPtr& request, std::function<void( const drogon::HttpResponsePtr& )>&& callback, std::string name ) const;
};

} // namespace Network

#endif // IMAGECONTROLLER_H
