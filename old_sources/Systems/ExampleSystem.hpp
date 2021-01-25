#ifndef INDIE_STUDIO_EXAMPLESYSTEM_HPP
#define INDIE_STUDIO_EXAMPLESYSTEM_HPP

#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "Components/Transform.hpp"
#include "Components/Speed.hpp"

class ExampleSystem : public ECS::System {
	void tick(ECS::World &world, float deltaTime) override;

private:
};

#endif
