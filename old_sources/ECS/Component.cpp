#include "Component.hpp"

std::size_t ECS::Component::type() {
    return typeid(*this).hash_code();
}
