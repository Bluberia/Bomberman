#ifndef INDIE_STUDIO_UPDATEBOMBYSTEM_HPP
#define INDIE_STUDIO_UPDATEBOMBYSTEM_HPP

#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "Components/Transform.hpp"
#include "Components/Speed.hpp"

class UpdateBomb : public ECS::System {
    void tick(ECS::World &world, float deltaTime) override;

private:
};

#endif
