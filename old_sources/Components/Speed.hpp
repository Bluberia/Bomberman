#ifndef INDIE_STUDIO_SPEED_HPP
#define INDIE_STUDIO_SPEED_HPP

#include <ostream>
#include "ECS/Component.hpp"
#include "Vector3D.hpp"

namespace ECS
{
    namespace Components
    {
        class Speed : public ECS::Component
        {
        public:
            Speed() : speed(0)
            {}

            Speed(Vector3D<float> &speed) : speed(speed)
            {}

            ~Speed() override = default;

            friend std::ostream &operator<<(std::ostream &os, const Speed &speed)
            {
                os << "speed: " << speed.speed;
                return os;
            }

            Vector3D<float> speed;
        };
    }
}

#endif