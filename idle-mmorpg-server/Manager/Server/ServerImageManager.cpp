#include "ServerImageManager.h"

#include <fstream>
#include <iostream>

namespace Engine {

bool ServerImageManager::loadImage( const std::string& id, const std::string& filePath ) {
    if ( hasImage( id ) ) {
        return true;
    }

    std::ifstream file( filePath, std::ios::binary );
    if ( !file.is_open() ) {
        std::cerr << "ServerImageManager: failed to load image: " << filePath << std::endl;
        return false;
    }

    std::vector<unsigned char> buffer( ( std::istreambuf_iterator<char>( file ) ), std::istreambuf_iterator<char>() );

    _images[ id ] = std::move( buffer );

    return true;
}

bool ServerImageManager::hasImage( const std::string& id ) const {
    return _images.find( id ) != _images.end();
}

const std::vector<unsigned char>* ServerImageManager::imageById( const std::string& id ) const {
    auto it = _images.find( id );
    if ( it == _images.end() ) {
        return nullptr;
    }

    return &it->second;
}

} // namespace Engine
