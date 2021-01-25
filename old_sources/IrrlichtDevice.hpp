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

#include <string>
#include "MyEventReceiver.hpp"

class IrrlichtDevice {
public:
    IrrlichtDevice(bool driverChoice);
    ~IrrlichtDevice();

    irr::IrrlichtDevice* getDevice() const;
    irr::video::IVideoDriver* getDriver() const;
    irr::scene::ISceneManager* getManager() const;

    irr::scene::IAnimatedMesh* loadMesh(const irr::io::path &pathMesh);
    irr::scene::IAnimatedMeshSceneNode* loadSceneNode(irr::scene::IAnimatedMesh* mesh);
    irr::scene::IAnimatedMeshSceneNode* loadTextureModels(const irr::io::path &pathTexture, irr::scene::IAnimatedMeshSceneNode* model, bool transparent);
    irr::scene::IAnimatedMeshSceneNode* loadAnimation(irr::core::vector2di frameLoop, int animationSpeed, irr::scene::IAnimatedMeshSceneNode* model);
    irr::scene::ICameraSceneNode* loadCamera(irr::core::vector3df position, irr::core::vector3df rotation, irr::core::vector3df target);
    irr::scene::ISceneNode* loadCube();
    irr::scene::ISceneNode* loadTextureCube(const irr::io::path &pathTexture, irr::scene::ISceneNode* model, bool transparent);

    void drawWindow();

public:
    irr::IrrlichtDevice* _device;
    irr::video::IVideoDriver* _driver;
    irr::scene::ISceneManager* _smgr;
    MyEventReceiver _receiver;
};

#endif
