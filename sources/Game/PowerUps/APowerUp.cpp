#include "APowerUp.hpp"

APowerUp::APowerUp(std::string texture, irr::core::vector3df position) : Cube(texture)
{
    _defaultScale = {.75, .75, .75};
    _defaultRotation = {90, -90, 0};
    _defaultPosition = position;
    _type = GameObject::POWERUP;
    createObject();
    addCollision();
}

void APowerUp::update(std::vector<std::shared_ptr<GameObject>> &cubes) {
    auto rotation  = getRotation();

    rotation.Y += 100 * IrrlichtDevice::getInstance().getFrameDeltaTime();
    if (rotation.Y > 360)
        rotation.Y = 0;
    setRotation(rotation);
    GameObject::update(cubes);
}

void APowerUp::onOverlap(GameObject &player) {
    setDeleted(true);
    getNode()->setVisible(false);
}