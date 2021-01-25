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
#include "AssetManager.hpp"
#include "Bomberman.hpp"

IrrlichtDevice::IrrlichtDevice() :
    _device(nullptr),
    _driver(nullptr),
    _smgr(nullptr),
    _metaSelector(nullptr)
{
    irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL;
    _device = irr::createDevice(driverType, irr::core::dimension2d<irr::u32>(1920, 1080), 16, false, false, false, &_receiver);
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

    if (mesh == nullptr)
        throw(IndieException("Error : Create mesh failed", std::string(__FILE__) + std::to_string(__LINE__)));
    return mesh;
}

irr::scene::IAnimatedMeshSceneNode* IrrlichtDevice::loadSceneNode(irr::scene::IAnimatedMesh* mesh)
{
    irr::scene::IAnimatedMeshSceneNode* model = _smgr->addAnimatedMeshSceneNode(mesh);

    if (model == nullptr)
        throw(IndieException("Error : Create model failed", std::string(__FILE__) + std::to_string(__LINE__)));
    return model;
}

irr::scene::IAnimatedMeshSceneNode* IrrlichtDevice::loadTextureModels(irr::video::ITexture* texture, irr::scene::IAnimatedMeshSceneNode* model, bool transparent)
{
    model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    model->setMaterialTexture(0, texture);
    if (transparent == true)
        model->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
    return model;
}

irr::scene::ISceneNode* IrrlichtDevice::loadCube()
{
    irr::scene::ISceneNode* model = _smgr->addCubeSceneNode();

    if (model == nullptr)
        throw(IndieException("Error : Cube mesh failed", std::string(__FILE__) + std::to_string(__LINE__)));
    return model;
}

irr::scene::ISceneNode* IrrlichtDevice::loadTextureCube(irr::video::ITexture* texture, irr::scene::ISceneNode* model, bool transparent)
{
    model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    model->setMaterialTexture(0, texture);
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

irr::scene::ICameraSceneNode* IrrlichtDevice::loadCamera(const irr::core::vector3df& position, const irr::core::vector3df& rotation, const irr::core::vector3df& target)
{
    irr::scene::ICameraSceneNode *camera = _smgr->addCameraSceneNode(0, position, rotation);

    if (camera == nullptr)
        throw(IndieException("Error : Camera mesh failed", std::string(__FILE__) + std::to_string(__LINE__)));

    camera->setPosition(position);
    camera->setRotation(rotation);
    camera->setTarget(target);
    return camera;
}

void IrrlichtDevice::drawWindow(std::array<bool, 4> playersAlive)
{
    _smgr->drawAll();
    addIcon(playersAlive);
    _driver->endScene();
}

void IrrlichtDevice::addIcon(std::array<bool, 4> playersAlive) {
    if (playersAlive[0]) {
        IrrlichtDevice::getInstance()._driver->draw2DImage(AssetManager::getInstance().getTexture("whiteicon"),
                                                           irr::core::position2d<irr::s32>(300, 100),
                                                           irr::core::rect<irr::s32>(0, 0, 137, 141), 0,
                                                           irr::video::SColor(255, 255, 255, 255), true);
    } else
        IrrlichtDevice::getInstance()._driver->draw2DImage(AssetManager::getInstance().getTexture("deadicon"),
                                                           irr::core::position2d<irr::s32>(300, 100),
                                                           irr::core::rect<irr::s32>(0, 0, 137, 141), 0,
                                                           irr::video::SColor(255, 255, 255, 255), true);
    if (playersAlive[2]) {
        IrrlichtDevice::getInstance()._driver->draw2DImage(AssetManager::getInstance().getTexture("blackicon"),
                                                           irr::core::position2d<irr::s32>(300, 800),
                                                           irr::core::rect<irr::s32>(0, 0, 137, 141), 0,
                                                           irr::video::SColor(255, 255, 255, 255), true);
    } else
        IrrlichtDevice::getInstance()._driver->draw2DImage(AssetManager::getInstance().getTexture("deadicon"),
                                                           irr::core::position2d<irr::s32>(300, 800),
                                                           irr::core::rect<irr::s32>(0, 0, 137, 141), 0,
                                                           irr::video::SColor(255, 255, 255, 255), true);
    if (playersAlive[1]) {
        IrrlichtDevice::getInstance()._driver->draw2DImage(AssetManager::getInstance().getTexture("redicon"),
                                                           irr::core::position2d<irr::s32>(1500, 800),
                                                           irr::core::rect<irr::s32>(0, 0, 137, 141), 0,
                                                           irr::video::SColor(255, 255, 255, 255), true);
    } else
        IrrlichtDevice::getInstance()._driver->draw2DImage(AssetManager::getInstance().getTexture("deadicon"),
                                                           irr::core::position2d<irr::s32>(1500, 800),
                                                           irr::core::rect<irr::s32>(0, 0, 137, 141), 0,
                                                           irr::video::SColor(255, 255, 255, 255), true);
    if (playersAlive[3]) {
        IrrlichtDevice::getInstance()._driver->draw2DImage(AssetManager::getInstance().getTexture("pinkicon"),
                                                           irr::core::position2d<irr::s32>(1500, 100),
                                                           irr::core::rect<irr::s32>(0, 0, 137, 141), 0,
                                                           irr::video::SColor(255, 255, 255, 255), true);
    } else
        IrrlichtDevice::getInstance()._driver->draw2DImage(AssetManager::getInstance().getTexture("deadicon"),
                                                           irr::core::position2d<irr::s32>(1500, 100),
                                                           irr::core::rect<irr::s32>(0, 0, 137, 141), 0,
                                                           irr::video::SColor(255, 255, 255, 255), true);
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

IrrlichtDevice &IrrlichtDevice::getInstance()
{
    static IrrlichtDevice irrlicht;

    return irrlicht;
}

irr::scene::ICameraSceneNode *IrrlichtDevice::camera()
{
    irr::scene::ICameraSceneNode *_camera;

    if (_smgr->getActiveCamera() == nullptr)
        _camera = _smgr->addCameraSceneNode();
    else
        _camera = _smgr->getActiveCamera();

    if (_camera == nullptr)
        throw IndieException("Failed to get camera.", std::string(__FILE__) + std::to_string(__LINE__));
    return _camera;
}

irr::scene::IMetaTriangleSelector *IrrlichtDevice::getMetaSelector() {
    if (_metaSelector == nullptr)
        initMetaSelector();
    return _metaSelector;
}

void IrrlichtDevice::initMetaSelector()
{
    _metaSelector = IrrlichtDevice::getInstance().getManager()->createMetaTriangleSelector();
}

irr::u32 IrrlichtDevice::updateTime(const irr::u32 &now)
{
    _then = now;
    return (_then);
}

irr::f32 IrrlichtDevice::updateFrame(const irr::u32 &now)
{
    _frameDeltaTime = (irr::f32)(now - _then) / 1000.f;
    return (_frameDeltaTime);
}

irr::f32 IrrlichtDevice::getFrameDeltaTime() const {
    return _frameDeltaTime;
}
