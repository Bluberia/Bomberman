#include "Breakable.hpp"

Breakable::Breakable(Vector3D<float> &pPos, Vector3D<float> &pRot, Vector3D<float> &pSca) :
        Wall("box", pPos, pRot, pSca) {
    _type = BREAKABLE;
}

bool Breakable::isBreakable() {
    return true;
}
