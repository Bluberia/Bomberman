#include "Exception.hpp"
#include "IrrlichtDevice.hpp"
#include "GameObject.hpp"
#include <algorithm>
#include <cstdlib>
#include "APlayer.hpp"
#include "MapManager.hpp"
#include "Model.hpp"

void Model::loadModel() {
    setNode(IrrlichtDevice::getInstance().loadSceneNode(AssetManager::getInstance().getModel(_model)));
}

void Model::loadTexture() {
    IrrlichtDevice::getInstance().loadTextureModels(AssetManager::getInstance().getTexture(_texture), reinterpret_cast<irr::scene::IAnimatedMeshSceneNode *>(getNode()), false);
}

Model::Model(std::string model, std::string texture) : _model(model), _texture(texture) {
}

void Model::createObject() {
    loadModel();
    loadTexture();
    defaultTransform();
}

void Model::addAnimation(const std::string &name, int start, int end, int speed) {
    _animations[name] = {start, end, speed};
}

void Model::setAnimation(const std::string &name) {
    if (_currentAnimation == name)
        return;

    try {
        auto &animation = _animations.at(name);

        _currentAnimation = name;
        IrrlichtDevice::getInstance().loadAnimation(irr::core::vector2di(animation.X, animation.Y), animation.Z, (irr::scene::IAnimatedMeshSceneNode*)getNode());
    } catch (const std::out_of_range &e) {}
}