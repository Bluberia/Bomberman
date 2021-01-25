#ifndef INDIE_STUDIO_ANIMATION_HPP
#define INDIE_STUDIO_ANIMATION_HPP

#include <map>
#include <string>
#include <utility>
#include "ECS/Component.hpp"

namespace ECS
{
    namespace Components
    {

        class Animation : public ECS::Component
        {
        public:

            struct animation_d
            {
                int start;
                int end;
                int speed;
            };

            Animation() = default;
            ~Animation() = default;

            void setAnimation(const std::string &name, int start, int end, int speed)
            {
                animation_d data = {start, end, speed};
                animation.emplace(std::make_pair(name, data));
            }

            std::map<std::string, animation_d> animation;
        };

    }
}

#endif // !INDIE_STUDIO_ANIMATION_HPP