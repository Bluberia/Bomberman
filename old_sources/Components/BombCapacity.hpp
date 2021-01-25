#ifndef INDIE_STUDIO_BOMB_CAPACITY
#define INDIE_STUDIO_BOMB_CAPACITY

#include "ECS/Component.hpp"

namespace ECS {
    namespace Components {
        class BombCapacity : public ECS::Component {
            public:
            BombCapacity(int capacity) : capacity(capacity) {
            }

            ~BombCapacity() override = default;

            int capacity;
        };
    }
}

#endif