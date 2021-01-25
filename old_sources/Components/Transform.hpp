#ifndef INDIE_STUDIO_TRANSFORM_HPP
#define INDIE_STUDIO_TRANSFORM_HPP

#include <ostream>
#include "Vector3D.hpp"
#include "ECS/Component.hpp"

namespace ECS
{
    namespace Components
    {
        class Transform : public ECS::Component
        {
        public:
            Transform() : position(0), rotation(0), scale(1)
            {}

            Transform(const Vector3D<float> &position, const Vector3D<float> &rotation, const Vector3D<float> &scale) :
                position(position),
                rotation(rotation),
                scale(scale)
            {
            }

            void lookAt(const Vector3D<float> &look)
            {
                //TODO
            }

            ~Transform() override = default;

            friend std::ostream &operator<<(std::ostream &os, const Transform &transform)
            {
                os << "position: " << transform.position << std::endl << "rotation: " << transform.rotation << std::endl
                   << "scale: " << transform.scale;
                return os;
            }

            Vector3D<float> position;
            Vector3D<float> rotation;
            Vector3D<float> scale;
        };
    }
}

#endif
