#ifndef INDIE_STUDIO_MESH_HPP
#define INDIE_STUDIO_MESH_HPP

#include "ECS/Component.hpp"

namespace ECS {
    namespace Components {
        class Mesh : public ECS::Component {
        public:
            Mesh(const std::string &path) : path(path) {
            }

            ~Mesh() override = default;

            const std::string &path;
        };
    }
}

#endif