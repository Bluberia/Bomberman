#ifndef INDIE_STUDIO_IA_HPP
#define INDIE_STUDIO_IA_HPP

#include "ECS/Component.hpp"

namespace ECS {
    namespace Components {
        class IA : public ECS::Component {
        public:
            IA(bool ia) : ia(ia) {
            }

            ~IA() override = default;

            bool ia;
        };
    }
}

#endif