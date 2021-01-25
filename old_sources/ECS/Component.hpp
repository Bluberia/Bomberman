#ifndef INDIE_STUDIO_COMPONENT_HPP
#define INDIE_STUDIO_COMPONENT_HPP

#include <ostream>

namespace ECS {
    class Component {
    public:
        virtual ~Component() = default;

        std::size_t type();
    };
}

#endif