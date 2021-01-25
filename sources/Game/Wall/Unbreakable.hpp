#ifndef INDIE_STUDIO_UNBREAKABLE_HPP
#define INDIE_STUDIO_UNBREAKABLE_HPP

#include "Wall.hpp"

class Unbreakable : public Wall {
public:
    Unbreakable(Vector3D<float> &pPos, Vector3D<float> &pRot, Vector3D<float> &pSca);
};

#else

class Unbreakable;

#endif