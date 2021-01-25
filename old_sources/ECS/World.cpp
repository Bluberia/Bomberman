#include "World.hpp"

ECS::World::World(bool running) :
        _running(running),
        _entities(),
        _systems() {
}

void ECS::World::update() {
    for (auto &_i : _systems) {
        (*_i).tick(*this, 0);
    }
}

void ECS::World::run() {
    while (_running) {
        update();
    }
}
