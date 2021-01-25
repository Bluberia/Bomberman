#include "Ground.hpp"

Ground::Ground() : Wall("ground") {
    _defaultPosition = {-5,-5.5,-5};
    _defaultScale = {13,.1,15};
    createObject();
    addCollision();
}