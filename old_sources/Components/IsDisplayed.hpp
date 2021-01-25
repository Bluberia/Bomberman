#ifndef INDIE_STUDIO_IS_DISPLAYED_HPP
#define INDIE_STUDIO_IS_DISPLAYED_HPP

#include "ECS/Component.hpp"

namespace ECS {
    namespace Components {
        class IsDisplayed : public ECS::Component {
         public:
            IsDisplayed(bool display) : display(display) {
            }

            ~IsDisplayed() override = default;

            bool display;

        };
    }
}

#endif