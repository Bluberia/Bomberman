#include <cstddef>
#include <functional>
#include <memory>
#include "Entity.hpp"
#include "Exceptions/ComponentException.hpp"

int ECS::Entity::maxId = 0;

ECS::Entity::Entity() : _id() {
}

int ECS::Entity::getId() const {
    return _id;
}