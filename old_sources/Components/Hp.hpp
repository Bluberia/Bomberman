#ifndef INDIE_STUDIO_HP_HPP
#define INDIE_STUDIO_HP_HPP

#include "ECS/Component.hpp"

namespace ECS
{
    namespace Components
    {
        class Hp : public ECS::Component
        {
        public:
            Hp(int hp) : hp(hp)
            {
            }

            ~Hp() override = default;

            int hp;
        };
    }
}

#endif