#ifndef INDIE_STUDIO_ISCOLLIDING_HPP
#define INDIE_STUDIO_ISCOLLIDING_HPP

#include "ECS/System.hpp"
#include "ECS/World.hpp"

class IsColliding : public ECS::System {
    void tick(ECS::World& world, float deltaTime) override;

private:
};

#endif