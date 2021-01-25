#ifndef INDIE_STUDIO_ENTITY_HPP
#define INDIE_STUDIO_ENTITY_HPP

#include <vector>
#include <memory>
#include <functional>
#include <iostream>
#include "Component.hpp"
#include "Exceptions/ComponentException.hpp"

namespace ECS {
    class Entity {
    public:
        Entity();
        int getId() const;

        template <typename T, typename ...Args>
            void attach(Args ...args) {
                _components.emplace_back(new T(args...));
            }

        static int maxId;
    public:
        template <typename ComponentType>
        bool hasComponent() {
            for (auto &i : _components) {
                try {
                    dynamic_cast<ComponentType &>(*i);
                    return true;
                } catch (const std::bad_cast &e) {}
            }
            return (false);
        }

        template <typename ComponentType1, typename ComponentType2, typename ... OtherTypes>
        bool hasComponents() {
            return hasComponent<ComponentType1>() && hasComponents<ComponentType2, OtherTypes...>();
        }

        template <typename ComponentType1>
        bool hasComponents() {
            return hasComponent<ComponentType1>();
        }

        template <typename T>
        std::reference_wrapper<ECS::Component> getComponent() {
            for (auto &i : _components) {
                try {
                    return dynamic_cast<T &>(*i);
                } catch (const std::bad_cast &e) {}
            }
            throw ECS::ComponentException("Component " + std::string(typeid(T).name()) + " not found");
        };

        template <typename ComponentType1, typename ComponentType2, typename ...OtherTypes>
        std::tuple<std::reference_wrapper<ComponentType1>, std::reference_wrapper<ComponentType2>, std::reference_wrapper<OtherTypes>...> getComponents() {
            auto tuple1 = getComponents<ComponentType1>();
            auto tuple2 = getComponents<ComponentType2, OtherTypes...>();

            return std::tuple_cat(tuple1, tuple2);
        }

        template <typename ComponentType1>
        std::tuple<std::reference_wrapper<ComponentType1>> getComponents() {
            return std::make_tuple(std::ref(extractComp<ComponentType1>()));
        }

        template <typename CompType>
        CompType &extractComp() {
            return dynamic_cast<CompType &>(getComponent<CompType>().get());
        }

    private:
        int                                     _id;
        std::vector<std::unique_ptr<Component>> _components;
    };
}

#endif //INDIE_STUDIO_ENTITY_HPP
