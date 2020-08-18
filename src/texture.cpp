#include "teqi/canvas/texture.h"
#include "teqi/canvas/utility.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <gl/glew.h>
#include <glfw/glfw3.h>


namespace tq {


////////////////////////////////////////////////////////////////////////////////
Texture::Texture( const std::string& filepath, const bool mipmaps ) {
    fromFile( filepath, mipmaps );
}


////////////////////////////////////////////////////////////////////////////////
Texture::Texture( const uint32_t id ) :
    id_( id )
{
    TextureManager::retain( id_ );
}


////////////////////////////////////////////////////////////////////////////////
Texture::Texture(
    const uint32_t width,
    const uint32_t height,
    const uint8_t numChannels,
    const uint8_t* data,
    const bool mipmaps )
{
    fromData( width, height, numChannels, data, mipmaps );
}


////////////////////////////////////////////////////////////////////////////////
void Texture::use( const uint8_t unit ) const {
    glActiveTexture( GL_TEXTURE0 + unit );
    glBindTexture( GL_TEXTURE_2D, id_ );
}


////////////////////////////////////////////////////////////////////////////////
bool Texture::fromFile( const std::string& filepath, const bool mipmaps )
{
    if ( const uint32_t id = TextureManager::find( filepath.data() ) )
    {
        fmt::print( "reusing texture '{}' \n", filepath );

        id_ = id;
        TextureManager::retain( id );
        return true;
    }

    fmt::print( "loading texture from '{}' ... \n", filepath );

    int width, height, numChannels;

    stbi_set_flip_vertically_on_load( true );
    uint8_t* data = stbi_load( filepath.data(), &width, &height, &numChannels, 0 );

    if ( ! data ) {
        fmt::format( fg_error, "couldn't read texture '{}' \n", filepath );
        return false;
    }

    fromData( width, height, numChannels, data, mipmaps );
    stbi_image_free( data );

    TextureManager::insert( filepath.data(), id_ );
    return true;
}


////////////////////////////////////////////////////////////////////////////////
bool Texture::fromData(
    const uint32_t width,
    const uint32_t height,
    const uint8_t numChannels,
    const uint8_t* data,
    const bool mipmaps )
{
    fmt::print(
        "loading texture from data of size ({}, {}) with {} channels ... \n",
        width,
        height,
        numChannels
    );

    const GLint format = (
        ( numChannels == 1 ) ? GL_RED :
        ( numChannels == 3 ) ? GL_RGB :
        GL_RGBA
    );

    glGenTextures( 1, &id_ );
    glBindTexture( GL_TEXTURE_2D, id_ );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mipmaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data );

    if ( mipmaps ) {
        glHint( GL_GENERATE_MIPMAP_HINT, GL_NICEST );
        glGenerateMipmap( GL_TEXTURE_2D );
    }

    TextureManager::retain( id_ );
    return true;
}


////////////////////////////////////////////////////////////////////////////////
Texture::~Texture() {
    TextureManager::release( id_ );
}


////////////////////////////////////////////////////////////////////////////////
Texture::Texture( const Texture& other ) noexcept :
    id_ { other.id_ }
{
    TextureManager::retain( id_ );
}


////////////////////////////////////////////////////////////////////////////////
Texture& Texture::operator=( const Texture& other ) noexcept {
    id_ = other.id_;
    TextureManager::retain( id_ );
    return *this;
}


////////////////////////////////////////////////////////////////////////////////
Texture::Texture( Texture&& other ) noexcept :
    id_ { other.id_ }
{
    TextureManager::retain( id_ );
}


////////////////////////////////////////////////////////////////////////////////
Texture& Texture::operator=( Texture&& other ) noexcept {
    id_ = other.id_;
    TextureManager::retain( id_ );
    return *this;
}


////////////////////////////////////////////////////////////////////////////////
std::unordered_map<std::string, uint32_t> TextureManager::textureIds_ {};
std::unordered_map<uint32_t, int> TextureManager::referenceCounts_ {};


////////////////////////////////////////////////////////////////////////////////
uint32_t TextureManager::find( const std::string& key )
{
    if ( textureIds_.find( key ) == textureIds_.end() ) {
        return 0;
    }

    return textureIds_.at( key );
}

////////////////////////////////////////////////////////////////////////////////
void TextureManager::insert( const std::string& key, const uint32_t id )
{
    if ( const uint32_t currId = find( key ) ) {
        release( currId );
    }

    textureIds_[ key ] = id;
    retain( id );
}


////////////////////////////////////////////////////////////////////////////////
int TextureManager::retain( const uint32_t id )
{
    if ( id == 0 ) {
        return -1;
    }

    return ( ++referenceCounts_[ id ] );
}


////////////////////////////////////////////////////////////////////////////////
int TextureManager::release( const uint32_t id )
{
    if ( id == 0 ) {
        return -1;
    }

    if ( referenceCounts_.find( id ) == referenceCounts_.end() ) {
        return 0;
    }

    auto& count = referenceCounts_.at( id );

    //  delete last instance
    if ( count == 1 ) {
        glDeleteTextures( 1, &id );
    }

    return ( --referenceCounts_.at( id ) );
}


}   //  ::tq