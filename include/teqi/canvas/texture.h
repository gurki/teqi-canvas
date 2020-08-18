#pragma once

#include <gl/glew.h>
#include <string_view>
#include <unordered_map>

namespace tq {


struct Texture
{
    Texture() {};
    Texture( const std::string& filepath, const bool mipmaps = true );
    Texture( const uint32_t id );
    Texture(
        const uint32_t width,
        const uint32_t height,
        const uint8_t numChannels,
        const uint8_t* data,
        const bool mipmaps = true
    );

    ~Texture();

    bool valid() const { return id_ != 0; }
    uint32_t id() const { return id_; }

    void use( const uint8_t unit = 0 ) const;

    Texture( const Texture& ) noexcept;
    Texture& operator=( const Texture& ) noexcept;
    Texture( Texture&& ) noexcept;
    Texture& operator=( Texture&& ) noexcept;

    private:

        bool fromFile( const std::string& filepath, const bool mipmaps );

        bool fromData(
            const uint32_t width,
            const uint32_t height,
            const uint8_t numChannels,
            const uint8_t* data,
            const bool mipmaps
        );

        uint32_t id_ = 0;
};

// Texture loadTexture( const std::string& filepath );
// Texture createTexture(
//     const uint32_t width,
//     const uint32_t height,
//     const uint8_t numChannels,
//     const uint8_t* data
// );


struct TextureManager
{
    static uint32_t find( const std::string& key );
    static void insert( const std::string& key, const uint32_t id );
    static int retain( const uint32_t id );
    static int release( const uint32_t id );

    private:

        static std::unordered_map<std::string, uint32_t> textureIds_;
        static std::unordered_map<uint32_t, int> referenceCounts_;
};


}   //  :tq