#include "SplashScreen.hpp"
#include "AssetManager.hpp"

SplashScreen::SplashScreen() {
    AssetManager::getInstance().loadTexture("loading", "resources/ui/loading.png");
    IrrlichtDevice::getInstance()._driver->beginScene(true, true, irr::video::SColor(0,200,200,200));
    IrrlichtDevice::getInstance()._driver->draw2DImage(AssetManager::getInstance().getTexture("loading"), irr::core::position2d<irr::s32>(0,0));
    IrrlichtDevice::getInstance()._driver->endScene();
}