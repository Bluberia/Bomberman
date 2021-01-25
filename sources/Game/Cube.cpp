#include "Cube.hpp"

void Cube::createObject() {
    loadTexture();
    defaultTransform();
}

void Cube::loadTexture() {
    setNode(IrrlichtDevice::getInstance().loadCube());
    IrrlichtDevice::getInstance().loadTextureCube(AssetManager::getInstance().getTexture(_texture), getNode(), false);
}

Cube::Cube(std::string texture, double lifespan) : GameObject(lifespan), _texture(texture) {
}
