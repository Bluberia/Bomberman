
#include "ECS/Entity.hpp"
#include "Components/Transform.hpp"
#include "Components/Speed.hpp"
#include "Components/Hp.hpp"
#include "Components/Score.hpp"
#include "Components/Position.hpp"
#include "Components/Rotation.hpp"
#include "Components/IsDisplayed.hpp"
#include "Components/Mesh.hpp"
#include "Components/Texture.hpp"
#include "Components/Animation.hpp"

namespace ECS
{
    namespace Entities
    {
        class Player : public ECS::Entity
        {
            Player()
            {
                attach<ECS::Components::Transform>();
                attach<ECS::Components::Score>(0);
                attach<ECS::Components::Hp>(1);
                attach<ECS::Components::IsDisplayed>(true);
                //TODO: set mesh and texture path
                attach<ECS::Components::Mesh>("resources/Bomberman/Bomberman.MD3");
                attach<ECS::Components::Texture>("resources/Bomberman/WhiteBombermanTextures.png");
                attach<ECS::Components::Animation>();




            }

            ~Player() = default;
        };
    }
}
