#ifndef INDIE_STUDIO_WALL_HPP
#define INDIE_STUDIO_WALL_HPP

#include "ECS/Entity.hpp"
#include "Components/Transform.hpp"
#include "Components/Position.hpp"
#include "Components/IsDisplayed.hpp"
#include "Components/Mesh.hpp"
#include "Components/Texture.hpp"
#include "Components/Collision.hpp"

namespace ECS
{
    namespace Entities
    {
        class Wall : public ECS::Entity
        {
        public:
            Wall() : Wall(Vector3D<float>(0), Vector3D<float>(0), Vector3D<float>(1))
            {}

            Wall(Vector3D<float> p_pos, Vector3D<float> p_rot, Vector3D<float> p_scale)
            {
                Vector3D<float> hitbox(0);

                attach<ECS::Components::Transform>(p_pos, p_rot, p_scale);
                attach<ECS::Components::IsDisplayed>(true);
                //TODO: set mesh and textures path
                attach<ECS::Components::Mesh>("Mesh Path");
                attach<ECS::Components::Texture>("Texture path");
                attach<ECS::Components::Collision>(true, hitbox);
            }
        };

    }
}

#endif
