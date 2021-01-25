#ifndef INDIE_STUDIO_WORLD_HPP
#define INDIE_STUDIO_WORLD_HPP

#include <vector>
#include <algorithm>
#include "Entity.hpp"
#include "System.hpp"

namespace ECS {
    class World {
    public:
        World(bool running = true);
        void update();
        void run();

        template <typename EntKlass, typename ...Args>
            void addEntity(Args ...args) {
            _entities.emplace_back(new EntKlass(args...));
        }

        template <typename SysKlass, typename ...Args>
            void addSystem(Args ...args) {
            _systems.emplace_back(new SysKlass(args...));
        }

        template <typename ...CompType>
        void each(typename std::common_type<std::function<void (Entity &, std::tuple<std::reference_wrapper<CompType>...>)>>::type toApply) {
            for (auto &_i : _entities) {
                if (_i.operator*().hasComponents<CompType...>())
                    toApply(*_i, (*_i).getComponents<CompType...>());
            }
        }

    private:
        bool _running;
        std::vector<std::unique_ptr<ECS::Entity>> _entities;
        std::vector<std::unique_ptr<ECS::System>> _systems;
    };
}

#else

namespace ECS {
    class World;
}

#endif
