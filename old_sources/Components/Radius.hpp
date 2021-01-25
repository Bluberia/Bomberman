#ifndef INDIE_STUDIO_RADIUS_HPP
#define INDIE_STUDIO_RADIUS_HPP

#include "ECS/Component.hpp"

namespace ECS {
    namespace Components {
        class Radius : public ECS::Component {
        public:
            Radius(int range) : range(range) {
            }

            ~Radius() override = default;

            int range;
        };
    }
}

#endif