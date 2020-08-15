#pragma once 

#include <glm/vec2.hpp>

namespace tq {

class Window;


class Mouse
{
    public:

        Mouse( tq::Window* );

        void lock() const;
        void unlock() const;
        
        [[nodiscard]] glm::vec2 cursorPosition() const;
        [[nodiscard]] bool pressed( const uint32_t button ) const;
        [[nodiscard]] bool released( const uint32_t button ) const;

    private:

        tq::Window* window_ = nullptr;
};


}   //  ::tq