#ifndef INDIE_STUDIO_TEXTURE_HPP
#define INDIE_STUDIO_TEXTURE_HPP

#include "ECS/Component.hpp"

namespace ECS {
    namespace Components {
        class Texture : public ECS::Component {
        public:
            Texture(const std::string &path) : path(path) {
            }

            ~Texture() override = default;

            const std::string &path;
        };
    }
}

#endif