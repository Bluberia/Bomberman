#ifndef INDIE_STUDIO_SCORE_HPP
#define INDIE_STUDIO_SCORE_HPP

#include "ECS/Component.hpp"

namespace ECS {
    namespace Components {
        class Score : public ECS::Component {
        public:
            Score(int score) : score(score) {
            }

            ~Score() override = default;
            
            int score;
        };
    }
}

#endif