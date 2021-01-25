#ifndef INDIE_STUDIO_BOMBUP_HPP
#define INDIE_STUDIO_BOMBUP_HPP

#include "APowerUp.hpp"

class BombUp : public APowerUp {
public:
    explicit BombUp(const irr::core::vector3df &pVec);
    void onOverlap(GameObject &player) override;
};

#else

class BombUp;

#endif