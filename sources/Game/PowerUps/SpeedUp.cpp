#include "SpeedUp.hpp"
#include "Player.hpp"

void SpeedUp::onOverlap(GameObject &player)
{
    try {
        auto &pl = dynamic_cast<APlayer &>(player);
        float nb = pl.getSpeed();

        if (nb < 9)
            pl.setSpeed(nb + 1);
    } catch (const std::bad_cast &e) {}
    APowerUp::onOverlap(player);
}

SpeedUp::SpeedUp(const irr::core::vector3df &pVec) :
        APowerUp("speedup", pVec) {
}
