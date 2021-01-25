#ifndef INDIE_STUDIO_SPEEDUP_HPP
#define INDIE_STUDIO_SPEEDUP_HPP

#include "APowerUp.hpp"

class SpeedUp : public APowerUp {
public:
    explicit SpeedUp(const irr::core::vector3df &pVec);
    void onOverlap(GameObject &player) override;
};

#else

class SpeedUp;

#endif