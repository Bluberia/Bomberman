#ifndef INDIE_STUDIO_BREAKABLE_HPP
#define INDIE_STUDIO_BREAKABLE_HPP

#include "Wall.hpp"

class Breakable : public Wall {
public:
    Breakable(Vector3D<float> &pPos, Vector3D<float> &pRot, Vector3D<float> &pSca);
    bool isBreakable() override;
};

#else

class Breakable;

#endif