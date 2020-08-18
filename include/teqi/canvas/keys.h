#pragma once

#include <cstdint>

namespace tq {

class Window;


class Keys
{
    public:

        Keys( tq::Window* window );

        bool pressed( const uint32_t key ) const;
        bool released( const uint32_t key ) const;

    private:

        tq::Window* window_ = nullptr;
};


}   //  ::tq