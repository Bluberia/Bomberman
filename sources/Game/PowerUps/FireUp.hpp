#ifndef INDIE_STUDIO_FIREUP_HPP
#define INDIE_STUDIO_FIREUP_HPP

#include "APowerUp.hpp"

class FireUp : public APowerUp {
public:
    explicit FireUp(const irr::core::vector3df &pVec);
    void onOverlap(GameObject &player) override;
};

#else

class FireUp;

#endif