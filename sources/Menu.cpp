
#include "Menu.hpp"
#include "MyEventReceiver.hpp"
#include "AssetManager.hpp"

Menu::Menu() : splashScreen(), _hasTwoPlayer(false), _isRenderingParameters(false), _isPlaying(false), bomberman() {
    loadAllTextures();
    IrrlichtDevice& irr = IrrlichtDevice::getInstance();
    _device = irr.getDevice();
    _driver = _device->getVideoDriver();
    _env = _device->getGUIEnvironment();
    addMainMenuButtons();
    render();
}

Menu::~Menu() {
}

void Menu::loadAllTextures()
{
    AssetManager::getInstance().loadTexture("start", "resources/menus/playButton.png");
    AssetManager::getInstance().loadTexture("quit", "resources/menus/quitButton.png");
    AssetManager::getInstance().loadTexture("load", "resources/menus/loadButton.png");
    AssetManager::getInstance().loadTexture("saveA", "resources/menus/saveAButton.png");
    AssetManager::getInstance().loadTexture("saveB", "resources/menus/saveBButton.png");
    AssetManager::getInstance().loadTexture("back", "resources/menus/backButton.png");
    AssetManager::getInstance().loadTexture("menu", "resources/menus/bigbackground.png");
}

void Menu::addMainMenuButtons()
{
    _env->clear();
    _quitButton = _env->addButton(irr::core::rect<irr::s32>(50,900,304,900 + 97), 0, MyEventReceiver::GUI_ID_QUIT_BUTTON, L"", L"Exits Program");
    _quitButton->setImage(AssetManager::getInstance().getTexture("quit")/*, irr::core::rect<irr::s32>(0,0,100,100)*/);
    _startNewGameButton = _env->addButton(irr::core::rect<irr::s32>(600,290,850,290 + 127), 0, MyEventReceiver::GUI_ID_START_GAME, L"", L"Launch a new Game");
    _startNewGameButton->setImage(AssetManager::getInstance().getTexture("start"));
    _loadMenuButton = _env->addButton(irr::core::rect<irr::s32>(1050,290,1300,290 + 127), 0, MyEventReceiver::GUI_ID_LOAD_GAME, L"", L"Load a previous Game");
    _loadMenuButton->setImage(AssetManager::getInstance().getTexture("load"));
    _parametersButton = _env->addButton(irr::core::rect<irr::s32>(1775,50,1865,50 + 78), 0, MyEventReceiver::GUI_ID_PARAMETERS, L"Toggle 2 Players Mode", L"Launch your next game in a twoPlayerMode");
    //_parametersButton->setImage(_parametersTexture);
}

void Menu::addLoadMenuButtons()
{
    _env->clear();
    _quitButton = _env->addButton(irr::core::rect<irr::s32>(50,900,304,900 + 97), 0, MyEventReceiver::GUI_ID_QUIT_BUTTON, L"", L"Exits Program");
    _quitButton->setImage(AssetManager::getInstance().getTexture("quit"));
    _loadSaveAButton = _env->addButton(irr::core::rect<irr::s32>(600,290,850,300 + 127), 0, MyEventReceiver::GUI_ID_LOAD_SAVE_A, L"", L"load first save");
    _loadSaveAButton->setImage(AssetManager::getInstance().getTexture("saveA"));
    _loadSaveBButton = _env->addButton(irr::core::rect<irr::s32>(1050,290,1300,300 + 127), 0, MyEventReceiver::GUI_ID_LOAD_SAVE_B, L"", L"Load second save");
    _loadSaveBButton->setImage(AssetManager::getInstance().getTexture("saveB"));
    _backButton = _env->addButton(irr::core::rect<irr::s32>(1740,25,1900,25 + 110), 0, MyEventReceiver::GUI_ID_BACK, L"", L"Return to Main Menu");
    _backButton->setImage(AssetManager::getInstance().getTexture("back"));
}

void Menu::render() {
    while(_device->run() && _driver) {
        _driver->beginScene(true, true, irr::video::SColor(255,120,102,136));
        _driver->draw2DImage(AssetManager::getInstance().getTexture("menu"), irr::core::rect<irr::s32>(0,0,1920,1080), irr::core::rect<irr::s32>(0,0,1920,1080));
        if (_device->isWindowActive()) {
            _env->drawAll();
            eventChecker();
            _driver->endScene();
        }
    }
}

void Menu::eventChecker() {
        auto &receiver = IrrlichtDevice::getInstance()._receiver;
        if (receiver.isButtonClicked(MyEventReceiver::GUI_ID_QUIT_BUTTON) || (receiver.IsKeyDown(irr::KEY_SPACE) && receiver.IsKeyDown(irr::KEY_ESCAPE))) {
            quit();
        } else if (receiver.isButtonClicked(MyEventReceiver::GUI_ID_START_GAME)) {
            bomberman.startGame(getHasTwoPlayer());
        } else if (receiver.isButtonClicked(MyEventReceiver::GUI_ID_LOAD_GAME)) {
            loadSaveScreen();
        } else if (receiver.isButtonClicked(MyEventReceiver::GUI_ID_PARAMETERS)) {
            _hasTwoPlayer = !_hasTwoPlayer;
        } else if (receiver.isButtonClicked(MyEventReceiver::GUI_ID_BACK)) {
            addMainMenuButtons();
        } else if (receiver.isButtonClicked(MyEventReceiver::GUI_ID_LOAD_SAVE_A)) {
            //Todo load save;
        } else if (receiver.isButtonClicked(MyEventReceiver::GUI_ID_LOAD_SAVE_B)) {
            //Inch on a deux saves
        }
}

void Menu::quit() {
    _env->clear();
    _driver->removeAllTextures();
    _device->closeDevice();
}

void Menu::loadSaveScreen()
{
    addLoadMenuButtons();
}

bool Menu::getHasTwoPlayer() {
    return _hasTwoPlayer;
}
