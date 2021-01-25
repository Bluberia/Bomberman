#ifdef _WIN32
    #include <irrlicht.h>
#else
    #include <irrlicht/irrlicht.h>
#endif

#include "ECS/World.hpp"
#include "Systems/ExampleSystem.hpp"
#include "ExampleEntity.hpp"
#include "Generation/MapGenerator.hpp"

int main(void)
{
    ECS::World world(true);
    MapGenerator generator;

    world.addSystem<ExampleSystem>();
    world.addEntity<ExampleEntity>();

    generator.generateWorld(world);

    world.run();
    return 0;
}
