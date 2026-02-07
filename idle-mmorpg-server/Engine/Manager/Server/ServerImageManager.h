#ifndef SERVERIMAGEMANAGER_H
#define SERVERIMAGEMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>

namespace Engine {

class ServerImageManager {
public:
    bool loadImage( const std::string& id, const std::string& filePath );
    bool hasImage( const std::string& id ) const;

    const std::vector<unsigned char>* imageById( const std::string& id ) const;

private:
    std::unordered_map<std::string, std::vector<unsigned char>> _images;
};

} // namespace Engine

#endif // SERVERIMAGEMANAGER_H
