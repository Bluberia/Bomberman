#include "BombUp.hpp"
#include "Player.hpp"

void BombUp::onOverlap(GameObject &player)
{
    try {
        auto &pl = dynamic_cast<APlayer &>(player);
        int nb = pl.getMaxBombCount();

        if (nb < 9)
            pl.setMaxBombCount(nb + 1);
    } catch (const std::bad_cast &e) {}
    APowerUp::onOverlap(player);
}

BombUp::BombUp(const irr::core::vector3df &pVec) :
        APowerUp("bombup", pVec) {
}