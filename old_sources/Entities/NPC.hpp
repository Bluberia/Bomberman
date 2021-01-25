
#include "ECS/Entity.hpp"
#include "Components/Transform.hpp"
#include "Components/Speed.hpp"
#include "Components/Hp.hpp"
#include "Components/Score.hpp"
#include "Components/Position.hpp"
#include "Components/Rotation.hpp"
#include "Components/IsDisplayed.hpp"
#include "Components/IA.hpp"
#include "Components/Mesh.hpp"
#include "Components/Animation.hpp"
#include "Components/Texture.hpp"


namespace ECS {
    namespace Entities {
        class NPC : public ECS::Entity
        {
            NPC() {
                attach<ECS::Components::Transform>();
                attach<ECS::Components::Score>(0);
                attach<ECS::Components::Hp>(1);
                attach<ECS::Components::IsDisplayed>(true);
                attach<ECS::Components::IA>(true);
                attach<ECS::Components::Mesh>("resources/Character/Bomberman.MD3");
                attach<ECS::Components::Texture>("resources/Character/RedBombermanTextures.png");
                attach<ECS::Components::Animation>();
            }

            ~NPC() = default;
        };
    }
}
