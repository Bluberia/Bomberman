#ifndef INDIE_STUDIO_MOVABLE_HPP
#define INDIE_STUDIO_MOVABLE_HPP

#include "ECS/Component.hpp"

namespace ECS {
    namespace Components {
        class Movable : public ECS::Component {
        public:
            Movable(bool movable) : movable(movable) {
            }

            ~Movable() override = default;

            bool movable;

        };
    }
}

#endif