/*
** EPITECH PROJECT, 2019
** Indie
** File description:
** Irrlicht Device
*/

#ifdef _WIN32
	#include <irrlicht.h>
	#include <driverChoice.h>
#else
	#include <irrlicht/irrlicht.h>
	#include <irrlicht/driverChoice.h>
#endif

#include "IrrlichtDevice.hpp"
#include "Exception.hpp"

IrrlichtDevice::IrrlichtDevice(bool driverChoice)
{
    irr::video::E_DRIVER_TYPE driverType;

    if (driverChoice == true) {
        driverType = irr::driverChoiceConsole();
        if (driverType == irr::video::EDT_COUNT)
            throw(IndieException("Error : Driver could not be loaded", std::string(__FILE__) + std::to_string(__LINE__)));
    } else
        driverType = irr::video::EDT_SOFTWARE;
    _device = irr::createDevice(driverType,
irr::core::dimension2d<irr::u32>(1920, 1080), 16, false, false, false, &_receiver);
    if (_device == nullptr)
        throw(IndieException("Error : Device creation failed", std::string(__FILE__) + std::to_string(__LINE__)));
    _device->setWindowCaption(L"Bomberman");
    _driver = _device->getVideoDriver();
    if (_driver == nullptr)
        throw(IndieException("Error : getting of the Driver failed", std::string(__FILE__) + std::to_string(__LINE__)));
    _smgr = _device->getSceneManager();
    if (_smgr == nullptr)
        throw(IndieException("Error : getting of the Scene Manager failed", std::string(__FILE__) + std::to_string(__LINE__)));
}

IrrlichtDevice::~IrrlichtDevice()
{
    _device->drop();
}

irr::scene::IAnimatedMesh* IrrlichtDevice::loadMesh(const irr::io::path &pathMesh)
{
    irr::scene::IAnimatedMesh* mesh = _smgr->getMesh(pathMesh);

    return mesh;
}

irr::scene::IAnimatedMeshSceneNode* IrrlichtDevice::loadSceneNode(irr::scene::IAnimatedMesh* mesh)
{
    irr::scene::IAnimatedMeshSceneNode* model = _smgr->addAnimatedMeshSceneNode(mesh);

    return model;
}


irr::scene::IAnimatedMeshSceneNode* IrrlichtDevice::loadTextureModels(const irr::io::path &pathTexture, irr::scene::IAnimatedMeshSceneNode* model, bool transparent)
{
    model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    model->setMaterialTexture(0, _driver->getTexture(pathTexture));
    if (transparent == true)
        model->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
    return model;
}

irr::scene::ISceneNode* IrrlichtDevice::loadCube()
{
    irr::scene::ISceneNode* model = _smgr->addCubeSceneNode();

    return model;
}

irr::scene::ISceneNode* IrrlichtDevice::loadTextureCube(const irr::io::path &pathTexture, irr::scene::ISceneNode* model, bool transparent)
{
    model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    model->setMaterialTexture(0, _driver->getTexture(pathTexture));
    if (transparent == true)
        model->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
    return model;
}

irr::scene::IAnimatedMeshSceneNode* IrrlichtDevice::loadAnimation(irr::core::vector2di frameLoop, int animationSpeed, irr::scene::IAnimatedMeshSceneNode* model)
{
    model->setFrameLoop(frameLoop.X, frameLoop.Y);
    model->setAnimationSpeed(animationSpeed);

    return model;
}

irr::scene::ICameraSceneNode* IrrlichtDevice::loadCamera(irr::core::vector3df position, irr::core::vector3df rotation, irr::core::vector3df target)
{
    irr::scene::ICameraSceneNode *camera = _smgr->addCameraSceneNode(0, position, rotation);

    camera->setTarget(target);
    return camera;
}

void IrrlichtDevice::drawWindow()
{
    _driver->beginScene(true, true, irr::video::SColor(0,200,200,200));

    _smgr->drawAll();
    _driver->endScene();
}

irr::IrrlichtDevice* IrrlichtDevice::getDevice() const
{
    return _device;
}

irr::video::IVideoDriver* IrrlichtDevice::getDriver() const
{
    return _driver;
}

irr::scene::ISceneManager* IrrlichtDevice::getManager() const
{
    return _smgr;
}
