#include "FireUp.hpp"
#include "Player.hpp"

void FireUp::onOverlap(GameObject &player)
{
    try {
        auto &pl = dynamic_cast<APlayer &>(player);

        int nb = pl.getBombPower();

        if (nb < 9)
            pl.setBombPower(nb + 1);
    } catch (const std::bad_cast &e) {}
    APowerUp::onOverlap(player);
}

FireUp::FireUp(const irr::core::vector3df &pVec) :
        APowerUp(std::string("fireup"), pVec) {
}
