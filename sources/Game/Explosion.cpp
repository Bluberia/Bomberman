#include "Explosion.hpp"
#include "IrrlichtDevice.hpp"
#include "AssetManager.hpp"
#include <APlayer.hpp>

void Explosion::onOverlap(GameObject &player) {
    try
    {
        auto& killedPlayer = dynamic_cast<APlayer&>(player);
        killedPlayer.kill();
    }
    catch (const std::bad_cast &e) {}
}

void Explosion::onCollide() {
}

const double Explosion::EXPLOSION_PERSISTENCE_TIME = 3;

Explosion::Explosion(const irr::core::vector3df &position) : Cube(std::string("fire"), EXPLOSION_PERSISTENCE_TIME)
{
    _type = GameObject::EXPLOSION;
    _defaultScale = {1, 1, 1};
    _defaultPosition = {position};

    createObject();
    addCollision();
}

void Explosion::onDeath(std::vector<std::shared_ptr<GameObject>> &cubes) {
    AssetManager::getInstance().playSound("BOMBEXPLODE");
    GameObject::onDeath(cubes);
}

Explosion::~Explosion() = default;

void Explosion::update(std::vector<std::shared_ptr<GameObject>>& cubes)
{
    auto entityCollided = isColliding(cubes);

    if (entityCollided != nullptr && (entityCollided->getType() == GameObject::PLAYER || entityCollided->getType() == GameObject::BREAKABLE)) {
        onOverlap(*entityCollided);
    }
    GameObject::update(cubes);
}