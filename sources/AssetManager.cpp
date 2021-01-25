#include <path.h>
#include <algorithm>
#include <IAnimatedMesh.h>
#include "AssetManager.hpp"
#include "Exception.hpp"

void AssetManager::loadModel(const std::string &name, const irr::io::path &filename)
{
    _models.emplace(name, IrrlichtDevice::getInstance().loadMesh(filename));
}

irr::scene::IAnimatedMesh* AssetManager::getModel(const std::string &name)
{
    try {
        return _models.at(name);
    } catch (const std::out_of_range &e) {}
    throw IndieException("Error: Could not get model " + name, std::string(__FILE__) + std::to_string(__LINE__));
}

void AssetManager::loadTexture(const std::string &name, const irr::io::path &filename)
{
    _textures.emplace(name, IrrlichtDevice::getInstance()._driver->getTexture(filename));
    if (_textures[name] == nullptr)
        throw(IndieException("Error : Create texture failed", std::string(__FILE__) + std::to_string(__LINE__)));

}

irr::video::ITexture* AssetManager::getTexture(const std::string &name)
{
    try {
        return _textures.at(name);
    } catch (const std::out_of_range &e) {}
    throw IndieException("Error: Could not get texture " + name, std::string(__FILE__) + std::to_string(__LINE__));
}

void AssetManager::setSound(const std::string &name, const std::string &path)
{
    _sounds.emplace(name, path);
}

std::string AssetManager::getSound(const std::string &name)
{
    try {
        return _sounds.at(name);
    } catch (const std::out_of_range &e) {}
    throw IndieException("Error: Could not get sound " + name, std::string(__FILE__) + std::to_string(__LINE__));
}

void AssetManager::initSound()
{
    _sound = irrklang::createIrrKlangDevice();
    if (_sound == nullptr)
        throw IndieException("Failed to initialize sound.", std::string(__FILE__) + std::to_string(__LINE__));
}

AssetManager &AssetManager::getInstance()
{
    static AssetManager assetManager;

    return assetManager;
}

AssetManager::~AssetManager() {
    if (_sound != nullptr) {
        _sound->stopAllSounds();
        std::for_each(_soundsList.begin(), _soundsList.end(), [] (irrklang::ISound *ISound) {
            if (ISound)
                ISound->drop();
        });
        _sound->drop();
    }
}

void AssetManager::playSound(const std::string &name, bool loop) {
    _soundsList.push_back(_sound->play2D(AssetManager::getInstance().getSound(name).c_str(), loop));
}

AssetManager::AssetManager() : _sounds(), _sound(), _models(), _textures(), _soundsList() {
}

irrklang::ISoundEngine *AssetManager::getSound() const {
    return _sound;
}
