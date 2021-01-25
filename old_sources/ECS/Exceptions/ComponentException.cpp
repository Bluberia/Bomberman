#include "ComponentException.hpp"

ECS::ComponentException::ComponentException(const std::string &err) : _err(err) {
}

const char *ECS::ComponentException::what() const noexcept {
    return _err.c_str();
}
