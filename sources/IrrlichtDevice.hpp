/*
** EPITECH PROJECT, 2019
** Indie
** File description:
** Irrlicht Device
*/

#ifndef __IRRLICHT_DEVICE_HPP_
#define __IRRLICHT_DEVICE_HPP_


#ifdef _WIN32
#include <irrlicht.h>
#else
#include <irrlicht/irrlicht.h>
#endif

#include <array>
#include <string>
#include "MyEventReceiver.hpp"

class IrrlichtDevice {
public:
    static IrrlichtDevice& getInstance();
private:
    IrrlichtDevice();
public:
    ~IrrlichtDevice();

    irr::IrrlichtDevice* getDevice() const;
    irr::video::IVideoDriver* getDriver() const;
    irr::scene::ISceneManager* getManager() const;

    irr::scene::IAnimatedMesh* loadMesh(const irr::io::path& pathMesh);
    irr::scene::IAnimatedMeshSceneNode* loadSceneNode(irr::scene::IAnimatedMesh* mesh);
    irr::scene::IAnimatedMeshSceneNode* loadTextureModels(irr::video::ITexture* texture, irr::scene::IAnimatedMeshSceneNode* model, bool transparent);
    irr::scene::IAnimatedMeshSceneNode* loadAnimation(irr::core::vector2di frameLoop, int animationSpeed, irr::scene::IAnimatedMeshSceneNode* model);
    irr::scene::ICameraSceneNode* camera();
    irr::scene::ICameraSceneNode* loadCamera(const irr::core::vector3df& position, const irr::core::vector3df& rotation, const irr::core::vector3df& target);
    irr::scene::ISceneNode* loadCube();
    irr::scene::ISceneNode* loadTextureCube(irr::video::ITexture* texture, irr::scene::ISceneNode* model, bool transparent);
    irr::scene::IMetaTriangleSelector *getMetaSelector();
    irr::u32 updateTime(const irr::u32 &now);
    irr::f32 updateFrame(const irr::u32 &now);

    void addIcon(std::array<bool, 4> playersAlive);

    void drawWindow(std::array<bool, 4> playersAlive);

public:
    irr::IrrlichtDevice* _device;
    irr::video::IVideoDriver* _driver;
    irr::scene::ISceneManager* _smgr;
    irr::scene::IMetaTriangleSelector* _metaSelector;
    MyEventReceiver _receiver;
    irr::f32 getFrameDeltaTime() const;

private:
    void initMetaSelector();

    irr::f32 _frameDeltaTime;
    irr::u32 _then;
};


#else

class IrrlichtDevice;

#endif