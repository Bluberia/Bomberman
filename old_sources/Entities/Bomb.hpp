#ifndef INDIE_STUDIO_BOMB_HPP
#define INDIE_STUDIO_BOMB_HPP

#include "ECS/Entity.hpp"
#include "Components/Transform.hpp"
#include "Components/IsDisplayed.hpp"
#include "Components/Mesh.hpp"
#include "Components/Texture.hpp"
#include "Components/Animation.hpp"
#include "BombCapacity.hpp"
#include "BombTimer.hpp"

namespace ECS
{
    namespace Entities
    {
        class Bomb : public ECS::Entity
        {
            Bomb()
                {
                    attach<ECS::Components::Transform>();
                    attach<ECS::Components::IsDisplayed>(true);
                    attach<ECS::Components::Mesh>("resources/Bomb/Bomb.obj");
                    attach<ECS::Components::Texture>("resources/Bomb/Bomb.png");
                    attach<ECS::Components::Animation>();
                    attach<ECS::Components::BombCapacity>(2);
                    attach<ECS::Components::BombTimer>();
                }

            ~Bomb() = default;
        };
    }
}

#endif
