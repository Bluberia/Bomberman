/*
** EPITECH PROJECT, 2019
** Indie
** File description:
** Bomberman
*/


#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif


#include <random>
#include <algorithm>
#include <chrono>

#include "Wall/Ground.hpp"
#include "Bomberman.hpp"
#include "IrrlichtDevice.hpp"
#include "MapManager.hpp"
#include "Menu.hpp"
#include "Exception.hpp"
#include "AssetManager.hpp"
#include "Bot.hpp"
#include "Wall/Wall.hpp"
#include "Wall/Background.hpp"

Bomberman::Bomberman() :
    _running(true),
    soloGame(true)
{
    createAssets();
}

void Bomberman::setRunning(bool running) {
    _running = running;
}

Bomberman::~Bomberman()
{
}

void Bomberman::startGame(bool hasTwoPlayers)
{
    soloGame = hasTwoPlayers;
    runGame();
}

void Bomberman::createPlayers(int playerCount)
{
    for (int i = 1; i <= playerCount; i++) {
        auto *newPlayer = new Player(i);
        if (i == 2)
            newPlayer->setKeys({irr::KEY_UP, irr::KEY_LEFT, irr::KEY_DOWN, irr::KEY_RIGHT, irr::KEY_RCONTROL});
        _cubes.emplace_back(newPlayer);
    } for (int i = playerCount + 1; i <= 4; i++)
        _cubes.emplace_back(new Bot(i));
}

void Bomberman::createMap()
{
    std::random_device engine;
    std::uniform_int_distribution<int> distribution;
    MapManager generator(static_cast<unsigned int>(distribution(engine)));

    generator.generateWorld(_cubes);
    std::for_each(_cubes.begin(), _cubes.end(), [&] (std::shared_ptr<GameObject> &cube) {
        try {
            auto &player = dynamic_cast<APlayer &>(*cube);

            switch (player.getPlayerId()) {
                case 1:
                    player.setPosition(irr::core::vector3df(generator.getLeftUpperCorner()));
                    break;
                case 2:
                    player.setPosition(irr::core::vector3df(generator.getRightLowerCorner()));
                    break;
                case 3:
                    player.setPosition(irr::core::vector3df(generator.getLeftLowerCorner()));
                    break;
                case 4:
                    player.setPosition(irr::core::vector3df(generator.getRightUpperCorner()));
                    break;
            }
        } catch (const std::bad_cast &e) {}
    });
    _cubes.emplace_back(new Ground());
    _cubes.emplace_back(new Background());
}

void Bomberman::checkExit() {
    if (IrrlichtDevice::getInstance()._receiver.IsKeyDown(irr::KEY_ESCAPE))
        setRunning(false);
}

bool Bomberman::running() {
    return _running && IrrlichtDevice::getInstance()._device->run();
}

void Bomberman::setupCamera() {
    auto* camera = IrrlichtDevice::getInstance().camera();

    camera->setPosition({ -100, 300, 0 });
    camera->setFOV(.55f);
    camera->setTarget({ 0, 0, 0 });
}

void Bomberman::runGame() {
    setRunning(true);
    IrrlichtDevice& irr = IrrlichtDevice::getInstance();

    AssetManager::getInstance().playSound("MUSIC", true);
    createPlayers(soloGame ? 2 : 1);
    createMap();
    setupCamera();

    while (running()) {
        irr._driver->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));

        for (size_t i = 0; i < _cubes.size(); i++)
        {
            if (!_cubes.at(i)->isDeleted())
                _cubes.at(i)->update(_cubes);
        }
        checkExit();
        checkEndGame();

        const irr::u32 now = irr._device->getTimer()->getTime();
        irr.updateFrame(now);
        irr.updateTime(now);
        irr.drawWindow(checkAlive(getPlayers()));

        for (size_t i = 0; i < _cubes.size(); i++) {
            if (_cubes.at(i)->isDeleted()) {
                _cubes.erase(_cubes.begin() + i);
            }
        }
    }
    exitGame();
}

std::array<bool, 4> Bomberman::checkAlive(std::vector<std::shared_ptr<APlayer>> players) {
    std::array<bool, 4> playersAlive = {false, false, false, false};

    if (players[0]->isAlive())
        playersAlive[0] = true;
    if (players[1]->isAlive())
        playersAlive[1] = true;
    if (players[2]->isAlive())
        playersAlive[2] = true;
    if (players[3]->isAlive())
        playersAlive[3] = true;
    return (playersAlive);
}

void Bomberman::exitGame() {
    AssetManager::getInstance().getSound()->stopAllSounds();
    IrrlichtDevice::getInstance().getMetaSelector()->removeAllTriangleSelectors();
    _cubes.clear();
    IrrlichtDevice::getInstance().getManager()->clear();
}

void Bomberman::checkEndGame() {
    auto players = getPlayers();

    /* DEBUG KILL */
    auto &recv = IrrlichtDevice::getInstance()._receiver;
    std::array killKeys = {irr::KEY_F1, irr::KEY_F2, irr::KEY_F3, irr::KEY_F4, irr::KEY_F5};

    for (int i = 0; i < players.size(); ++i) {
        if (recv.IsKeyDown(killKeys[i]))
            players.at(i)->kill();
    }
    if (recv.IsKeyDown(killKeys[4]))
        std::for_each(players.begin(), players.end(), [] (std::shared_ptr<APlayer> p) {p->kill();});
    /* END OF DEBUG KILL */

    if (std::count_if(players.begin(), players.end(), [] (std::shared_ptr<APlayer> &player) {
        return player->isAlive();
    }) == 1) {
        auto winner = std::find_if(players.begin(), players.end(), [] (std::shared_ptr<APlayer> &player) {
        return player->isAlive();
    });
        victory(**winner);
    }

    if (std::count_if(players.begin(), players.end(), [] (std::shared_ptr<APlayer> &player) {
        return player->isAlive();
    }) == 0) {
        setRunning(false);
        drawEquality();
    }
}

std::vector<std::shared_ptr<APlayer>> Bomberman::getPlayers() {
    std::vector<std::shared_ptr<APlayer>> res;

    std::for_each(_cubes.begin(), _cubes.end(), [&res] (std::shared_ptr<GameObject> &cube) {
        try {
            if (cube->getType() == GameObject::PLAYER) {
                res.push_back(std::dynamic_pointer_cast<APlayer>(cube));
            }
        } catch (const std::bad_cast &e) {}
    });
    return res;
}

void Bomberman::victory(APlayer &player) {
    setRunning(false);
    drawVictory(player);
}

void Bomberman::drawVictory(APlayer &player) {
    IrrlichtDevice::getInstance()._driver->makeColorKeyTexture(AssetManager::getInstance().getTexture("win"), irr::video::SColor(255,0,0,0));
    IrrlichtDevice::getInstance()._driver->makeColorKeyTexture(AssetManager::getInstance().getTexture("1"), irr::video::SColor(255,0,0,0));
    IrrlichtDevice::getInstance()._driver->makeColorKeyTexture(AssetManager::getInstance().getTexture("2"), irr::video::SColor(255,0,0,0));
    IrrlichtDevice::getInstance()._driver->makeColorKeyTexture(AssetManager::getInstance().getTexture("3"), irr::video::SColor(255,0,0,0));
    IrrlichtDevice::getInstance()._driver->makeColorKeyTexture(AssetManager::getInstance().getTexture("4"), irr::video::SColor(255,0,0,0));

    IrrlichtDevice::getInstance()._driver->beginScene(true, true, irr::video::SColor(0,200,200,200));
    IrrlichtDevice::getInstance()._smgr->drawAll();
    IrrlichtDevice::getInstance()._driver->draw2DImage(AssetManager::getInstance().getTexture("win"), irr::core::position2d<irr::s32>(350,30), irr::core::rect<irr::s32>(0,0,1290,136), 0, irr::video::SColor(255,200,0,0), true);
    IrrlichtDevice::getInstance()._driver->draw2DImage(AssetManager::getInstance().getTexture(std::to_string(player.getPlayerId())), irr::core::position2d<irr::s32>(1135,30), irr::core::rect<irr::s32>(0,0,95,135), 0, irr::video::SColor(255,200,0,0), true);
    IrrlichtDevice::getInstance()._driver->endScene();

#ifdef _WIN32
    Sleep(3000);
#else
    sleep(3);
#endif // _WIN32
}

void Bomberman::drawEquality() {
    IrrlichtDevice::getInstance()._driver->makeColorKeyTexture(AssetManager::getInstance().getTexture("equality"), irr::video::SColor(255,0,0,0));

    IrrlichtDevice::getInstance()._driver->beginScene(true, true, irr::video::SColor(0,200,200,200));
    IrrlichtDevice::getInstance()._smgr->drawAll();
    IrrlichtDevice::getInstance()._driver->draw2DImage(AssetManager::getInstance().getTexture("equality"), irr::core::position2d<irr::s32>(750,25), irr::core::rect<irr::s32>(0,0,465,132), 0, irr::video::SColor(255,200,0,0), true);
    IrrlichtDevice::getInstance()._driver->endScene();

#ifdef _WIN32
    Sleep(3000);
#else
    sleep(3);
#endif // _WIN32
}

void Bomberman::createAssets()
{
    AssetManager::getInstance().initSound();
    AssetManager::getInstance().loadModel("bomberman", "resources/models/Character/Bomberman.MD3");
    AssetManager::getInstance().loadModel("powerup", "resources/models/PowerUp/PowerUp.obj");
    AssetManager::getInstance().loadModel("bomb", "resources/models/Bomb/Bomb.obj");
    AssetManager::getInstance().loadTexture("bomberman1", "resources/models/Character/Bomberman1.png");
    AssetManager::getInstance().loadTexture("bomberman2", "resources/models/Character/Bomberman2.png");
    AssetManager::getInstance().loadTexture("bomberman3", "resources/models/Character/Bomberman3.png");
    AssetManager::getInstance().loadTexture("bomberman4", "resources/models/Character/Bomberman4.png");
    AssetManager::getInstance().loadTexture("bombup", "resources/models/PowerUp/Bomb.png");
    AssetManager::getInstance().loadTexture("fireup", "resources/models/PowerUp/Fire.png");
    AssetManager::getInstance().loadTexture("speedup", "resources/models/PowerUp/Speed.png");
    AssetManager::getInstance().loadTexture("wallpass", "resources/models/PowerUp/Pass.png");
    AssetManager::getInstance().loadTexture("bomb", "resources/models/Bomb/Bomb.png");
    AssetManager::getInstance().loadTexture("wall", "resources/terrains/metal.jpg");
    AssetManager::getInstance().loadTexture("box", "resources/terrains/wood.jpg");
    AssetManager::getInstance().loadTexture("fire", "resources/terrains/explosion.png");
    AssetManager::getInstance().loadTexture("ground", "resources/terrains/terrain.jpg");
    AssetManager::getInstance().loadTexture("sky", "resources/terrains/sky.jpg");
    AssetManager::getInstance().loadTexture("win", "resources/terrains/win.png");
    AssetManager::getInstance().loadTexture("1", "resources/terrains/1.png");
    AssetManager::getInstance().loadTexture("2", "resources/terrains/2.png");
    AssetManager::getInstance().loadTexture("3", "resources/terrains/3.png");
    AssetManager::getInstance().loadTexture("4", "resources/terrains/4.png");
    AssetManager::getInstance().loadTexture("equality", "resources/terrains/equality.png");
    AssetManager::getInstance().loadTexture("blackicon", "resources/ui/BlackBombermanIcon.png");
    AssetManager::getInstance().loadTexture("pinkicon", "resources/ui/PinkBombermanIcon.png");
    AssetManager::getInstance().loadTexture("redicon", "resources/ui/RedBombermanIcon.png");
    AssetManager::getInstance().loadTexture("whiteicon", "resources/ui/WhiteBombermanIcon.png");
    AssetManager::getInstance().loadTexture("deadicon", "resources/ui/DeadBombermanIcon.png");
    IrrlichtDevice::getInstance()._driver->makeColorKeyTexture(AssetManager::getInstance().getTexture("whiteicon"),
                                                               irr::video::SColor(255, 0, 0, 255));
    IrrlichtDevice::getInstance()._driver->makeColorKeyTexture(AssetManager::getInstance().getTexture("deadicon"),
                                                               irr::video::SColor(255, 0, 0, 255));
    IrrlichtDevice::getInstance()._driver->makeColorKeyTexture(AssetManager::getInstance().getTexture("blackicon"),
                                                               irr::video::SColor(255, 0, 0, 255));
    IrrlichtDevice::getInstance()._driver->makeColorKeyTexture(AssetManager::getInstance().getTexture("redicon"),
                                                               irr::video::SColor(255, 0, 0, 255));
    IrrlichtDevice::getInstance()._driver->makeColorKeyTexture(AssetManager::getInstance().getTexture("pinkicon"),
                                                               irr::video::SColor(255, 0, 0, 255));
    AssetManager::getInstance().setSound("DEATH", "resources/sounds/Character/CharacterDeath.wav");
    AssetManager::getInstance().setSound("WALK", "resources/sounds/Character/CharacterWalk.wav");
    AssetManager::getInstance().setSound("BOMBPLACE", "resources/sounds/Bomb/PlaceBomb.wav");
    AssetManager::getInstance().setSound("BOMBEXPLODE", "resources/sounds/Bomb/BombExplode.wav");
    AssetManager::getInstance().setSound("MUSIC", "resources/sounds/Moments/Game-Musique.wav");
}
