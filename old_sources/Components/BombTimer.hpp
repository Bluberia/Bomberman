#ifndef INDIE_STUDIO_BOMB_TIMER
#define INDIE_STUDIO_BOMB_TIMER

#include "ECS/Component.hpp"

namespace ECS {
    namespace Components {
        class BombTimer : public ECS::Component {
        public:
            BombTimer() : timeLeft(3.f), cooking(true) {}
            explicit BombTimer(float timing) : timeLeft(timing), cooking(true) {}

            ~BombTimer() override = default;

            float timeLeft;
            bool cooking;
        };
    }
}

#endif