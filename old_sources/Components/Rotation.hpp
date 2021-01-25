#ifndef INDIE_STUDIO_ROTATION_HPP
#define INDIE_STUDIO_ROTATION_HPP

#include <ostream>
#include "ECS/Component.hpp"

namespace ECS {
    namespace Components {
        struct Rotation : public ECS::Component {
            Rotation(int X, int Y, int Z);

            int x;
            int y;
            int z;
        };
    }
}

#endif //INDIE_STUDIO_ROTATION_HPP
