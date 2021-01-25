#ifndef INDIE_STUDIO_POSITION_HPP
#define INDIE_STUDIO_POSITION_HPP

#include <ostream>
#include "ECS/Component.hpp"

namespace ECS {
    namespace Components {
        struct Position : public ECS::Component {
            Position(int X, int Y, int Z);

            int x;
            int y;
            int z;
        };
    }
}

#endif
