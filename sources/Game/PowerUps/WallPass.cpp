#include "WallPass.hpp"
#include "Player.hpp"

void WallPass::onOverlap(GameObject &player)
{
    try {
        auto &pl = dynamic_cast<APlayer &>(player);

        pl.setWallPass(true);
    } catch (const std::bad_cast &e) {}
    APowerUp::onOverlap(player);
}

WallPass::WallPass(const irr::core::vector3df &pVec) :
        APowerUp("wallpass", pVec) {
}