/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** No file there , just an Epitech header example
*/

#include "UpdateBomb.hpp"
#include "BombTimer.hpp"
#include "BombCapacity.hpp"

void UpdateBomb::tick(ECS::World &world, float deltaTime)
{
    world.each<ECS::Components::BombTimer, ECS::Components::BombCapacity>([&] (ECS::Entity &e, std::tuple<std::reference_wrapper<ECS::Components::BombTimer>, std::reference_wrapper<ECS::Components::BombCapacity>> tuple) {
        auto &timerComp = e.extractComp<ECS::Components::BombTimer>();
        auto &capaComp = e.extractComp<ECS::Components::BombCapacity>();

        if (timerComp.cooking) {
            timerComp.timeLeft -= deltaTime;
        }
        if (timerComp.timeLeft <= 0) {
            //TODO: explode bomb following the capaComp.capacity
        }
    });
}
