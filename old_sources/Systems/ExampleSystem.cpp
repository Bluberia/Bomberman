#include "ExampleSystem.hpp"

void ExampleSystem::tick(ECS::World &world, float deltaTime) {
    world.each<ECS::Components::Transform, ECS::Components::Speed>([&] (ECS::Entity &e, std::tuple<std::reference_wrapper<ECS::Components::Transform>, std::reference_wrapper<ECS::Components::Speed>> tuple) {
        auto &speedComp = e.extractComp<ECS::Components::Speed>();
        auto &transComp = e.extractComp<ECS::Components::Transform>();
        transComp.position.x += speedComp.speed.x;
        transComp.position.y += speedComp.speed.y;
        transComp.position.z += speedComp.speed.z;

        std::cout << transComp.position << std::endl;
    });
}
