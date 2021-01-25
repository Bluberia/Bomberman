#ifndef INDIE_STUDIO_COLLISION_HPP
#define INDIE_STUDIO_COLLISION_HPP

#include "Vector3D.hpp"
#include "ECS/Component.hpp"

namespace ECS
{
    namespace Components
    {
        class Collision : public ECS::Component
        {
        public:
            Collision(int collision, const Vector3D<float> &hitbox) : layerInd(collision), hitbox(hitbox)
            {
            }

            ~Collision() override = default;

            int layerInd;
            Vector3D<float> hitbox;
        };
    }
}

#endif
