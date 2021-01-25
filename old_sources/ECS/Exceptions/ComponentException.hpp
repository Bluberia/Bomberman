#ifndef INDIE_STUDIO_COMPONENTEXCEPTION_HPP
#define INDIE_STUDIO_COMPONENTEXCEPTION_HPP

#include "EcsException.hpp"
#include <string>

namespace ECS {
    class ComponentException : public ECSException {
    public:
        explicit ComponentException(const std::string &err);
        const char *what() const noexcept override;
    private:
        std::string _err;
    };
}

#endif