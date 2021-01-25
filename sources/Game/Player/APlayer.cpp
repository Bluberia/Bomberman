#include <algorithm>
#include <cstdlib>
#include "APlayer.hpp"
#include "IrrlichtDevice.hpp"
#include "MapManager.hpp"
#include "GameObject.hpp"
#include "Model.hpp"

APlayer::APlayer(int id) :
    _playerId(id),
    _speed(1),
    _bombPower(2),
    _wallPass(false),
    _maxBombCount(1),
    _bombs(),
    _alive(true),
    Model("bomberman", "bomberman" + std::to_string(id))
{
    _type = PLAYER;
    _defaultScale = {6, 6, 6};
    _defaultRotation = {0,90,0};
    createObject();
    addAnimation("idle", 27, 76, 30);
    addAnimation("walk", 0, 26, 30);
    setAnimation("idle");
    addCollision();
}

void APlayer::placeBomb(std::vector<std::shared_ptr<GameObject>> &cubes)
{
    if (_bombs.size() >= getMaxBombCount())
        return;
    std::shared_ptr<Bomb> newBomb(new Bomb(*this, getBombPower(), MapManager::evaluateTiledPosition(getPosition())));

    _bombs.push_back(newBomb);
    cubes.push_back(std::dynamic_pointer_cast<GameObject>(newBomb));
    AssetManager::getInstance().playSound("BOMBPLACE");
}

void APlayer::removeBomb(GameObject *bomb) {
    _bombs.erase(std::remove_if(_bombs.begin(), _bombs.end(), [&] (std::shared_ptr<Bomb> &toCheck) {
        return bomb == toCheck.get();
    }), _bombs.end());
}

void APlayer::update(std::vector<std::shared_ptr<GameObject>> &cubes) {
    std::cout << "Player " << getPlayerId() << " power: " << getBombPower() << " capacity: " << getMaxBombCount() << " speed: " << getSpeed() << " wallpass: " << canWallPass() << std::endl;

    auto entityCollided = isColliding(cubes);
    if (entityCollided != nullptr) {
        entityCollided->onOverlap(dynamic_cast<GameObject &>(*this));
    }
}

APlayer::~APlayer() {
}

void APlayer::kill() {
    if (!_alive)
        return;
    _alive = false;
    setAnimation("idle");
    setRotation({0, 0, 90});
}

void APlayer::moveUp()
{
    auto initial = getNode()->getPosition();

    setAnimation("walk");
    setPosition({initial.X + getSpeed() * 10 * IrrlichtDevice::getInstance().getFrameDeltaTime(), initial.Y, initial.Z});
    setRotation(irr::core::vector3df(0,-90,0));
}

void APlayer::moveDown()
{
    auto initial = getNode()->getPosition();

    setAnimation("walk");
    setPosition({initial.X - getSpeed() * 10 * IrrlichtDevice::getInstance().getFrameDeltaTime(), initial.Y, initial.Z});
    setRotation(irr::core::vector3df(0,90,0));
}

void APlayer::moveLeft()
{
    auto initial = getNode()->getPosition();

    setAnimation("walk");
    setPosition({initial.X, initial.Y, initial.Z + getSpeed() * 10 * IrrlichtDevice::getInstance().getFrameDeltaTime()});
    setRotation(irr::core::vector3df(0,180,0));
}

void APlayer::moveRight()
{
    auto initial = getNode()->getPosition();

    setAnimation("walk");
    getNode()->setPosition({initial.X, initial.Y, initial.Z - getSpeed() * 10 * IrrlichtDevice::getInstance().getFrameDeltaTime()});
    getNode()->setRotation(irr::core::vector3df(0,0,0));
}

bool APlayer::isAlive() const {
    return _alive;
}

const int APlayer::getPlayerId() const {
    return _playerId;
}

float APlayer::getSpeed() const {
    return _speed;
}

void APlayer::setSpeed(float speed) {
    _speed = speed;
}

int APlayer::getBombPower() const {
    return _bombPower;
}

void APlayer::setBombPower(int bombPower) {
    _bombPower = bombPower;
}

int APlayer::getMaxBombCount() const {
    return _maxBombCount;
}

void APlayer::setMaxBombCount(int maxBombCount) {
    _maxBombCount = maxBombCount;
}

bool APlayer::canWallPass() const {
    return _wallPass;
}

void APlayer::setWallPass(bool wallPass) {
    _wallPass = wallPass;
}

void APlayer::setPosition(const irr::core::vector3df &position) {
    GameObject::setPosition({position.X, 0, position.Z});
}
