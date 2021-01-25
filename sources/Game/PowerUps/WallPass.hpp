#ifndef INDIE_STUDIO_WALLPASS_HPP
#define INDIE_STUDIO_WALLPASS_HPP

#include "APowerUp.hpp"

class WallPass : public APowerUp {
public:
    explicit WallPass(const irr::core::vector3df &pVec);
    void onOverlap(GameObject &player) override;
};

#else

class WallPass;

#endif