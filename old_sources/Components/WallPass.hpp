#ifndef INDIE_STUDIO_WALL_PASS_HPP
#define INDIE_STUDIO_WALL_PASS_HPP

#include "ECS/Component.hpp"

namespace ECS {
    namespace Components {
        class WallPass : public ECS::Component {
        public:
            WallPass(bool pass) : pass(pass) {
            }

            ~WallPass() override = default;

            bool pass;
        };
    }
}

#endif