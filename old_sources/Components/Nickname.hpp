#ifndef INDIE_STUDIO_NICKNAME_HPP
#define INDIE_STUDIO_NICKNAME_HPP

#include "ECS/Component.hpp"

namespace ECS {
    namespace Components {
        class Nickname : public ECS::Component {
            public:
            Nickname(const std::string &name) : name(name) {
            }

            ~Nickname() override = default;

            const std::string &name;
        };
    }
}

#endif