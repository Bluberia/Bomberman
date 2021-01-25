#ifndef INDIE_STUDIO_ASSETMANAGER_HPP
#define INDIE_STUDIO_ASSETMANAGER_HPP

#include "irrlicht.hpp"
#include "IrrlichtDevice.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <irrKlang.h>

class AssetManager {
public:
    static AssetManager &getInstance();

    AssetManager(const AssetManager &) = delete;
    AssetManager operator=(const AssetManager &) = delete;
private:
    AssetManager();
    ~AssetManager();

public:
    void loadModel(const std::string &name, const irr::io::path &filename);
    irr::scene::IAnimatedMesh* getModel(const std::string &name);

    void loadTexture(const std::string &name, const irr::io::path &filename);
    irr::video::ITexture* getTexture(const std::string &name);

    void setSound(const std::string &name, const std::string &path);
    std::string getSound(const std::string &name);
    void playSound(const std::string &name, bool loop = false);

    void initSound();
    irrklang::ISoundEngine *getSound() const;

private:
    irrklang::ISoundEngine *_sound;
    std::map<std::string, irr::scene::IAnimatedMesh*> _models;
    std::map<std::string, irr::video::ITexture*> _textures;
    std::map<std::string, std::string> _sounds;
    std::vector<irrklang::ISound *> _soundsList;
};

#else

class AssetManager;

#endif
