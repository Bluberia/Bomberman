#include "ExampleEntity.hpp"
#include "Components/Speed.hpp"

ExampleEntity::ExampleEntity() {
    attach<ECS::Components::Transform>();
    attach<ECS::Components::Speed>();

    extractComp<ECS::Components::Speed>().speed.x = 10;
    std::cout << extractComp<ECS::Components::Transform>() << std::endl;
    std::cout << extractComp<ECS::Components::Speed>() << std::endl;

    std::cout << hasComponents<ECS::Components::Transform, ECS::Components::Speed>() << std::endl;
    auto components = getComponents<ECS::Components::Transform, ECS::Components::Speed>();
}
