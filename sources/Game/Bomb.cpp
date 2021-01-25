#include <algorithm>
#include "Exception.hpp"
#include "Breakable.hpp"
#include "Bomb.hpp"
#include "IrrlichtDevice.hpp"
#include "Explosion.hpp"
#include "MapManager.hpp"
#include "Wall.hpp"

const double Bomb::INITIAL_LIFESPAN = 25;

Bomb::Bomb(APlayer &p_player, int p_range, const irr::core::vector3df &p_pos) :
    _owner(p_player),
    _range(p_range),
    Model("bomb", "bomb")
{
    _type = BOMB;
    _defaultPosition = p_pos;
    _defaultScale = {1.1f, 1.1f, 1.1f};
    _lifespan = INITIAL_LIFESPAN;
    createObject();
    addCollision();
}

static void processExplosion(
    std::vector<std::shared_ptr<GameObject>> &p_cub,
    std::vector<irr::core::vector3df> &p_positions,
    const irr::core::vector3df &p_pos,
    const int p_range,
    const char p_okDir,
    MapManager::ECardinal p_dir
)
{
    auto cIte = std::find_if(p_cub.begin(), p_cub.end(), [&](std::shared_ptr<GameObject> cube) {
        return cube->getPosition() == MapManager::getPosAtDirAndRange(p_pos, p_dir, p_range);
    });
    if (p_okDir & ~p_dir && cIte == p_cub.end())
        p_positions.emplace_back(MapManager::getPosAtDirAndRange(p_pos, p_dir, p_range));
}

void Bomb::explode(std::vector<std::shared_ptr<GameObject>> &cubes)
{
    char okDir = 0b1111;
    MapManager::ECardinal dir;
    std::vector<irr::core::vector3df> positions;

    for (int i = 1; i <= _range; ++i) {
        std::for_each(cubes.begin(), cubes.end(), [&](std::shared_ptr<GameObject> &cube) {
            if (cube == nullptr)
                throw IndieException("Error: unknown behavior", std::string(__FILE__) + std::to_string(__LINE__));
            bool ret = cube->getType() == BREAKABLE;

            dir = MapManager::isInRange(getPosition(), cube->getPosition(), i);
            if (okDir & ~MapManager::NORTH && dir == MapManager::NORTH) {
            } else if (okDir & ~MapManager::WEST && dir == MapManager::WEST) {
            } else if (okDir & ~MapManager::SOUTH && dir == MapManager::SOUTH) {
            } else if (okDir & ~MapManager::EAST && dir == MapManager::EAST) {
            } else {
                ret = false;
            }
            if (ret) {
                positions.emplace_back((*cube).getPosition());
                try {
                    dynamic_cast<Breakable &>(*cube).breakWall(cubes);
                } catch (const std::bad_cast &e) {}
            }
            if (cube->isSolid()) {
                okDir = okDir & dir;
            }
            return ret;
        });
        processExplosion(cubes, positions, getPosition(), i, okDir, MapManager::NORTH);
        processExplosion(cubes, positions, getPosition(), i, okDir, MapManager::WEST);
        processExplosion(cubes, positions, getPosition(), i, okDir, MapManager::SOUTH);
        processExplosion(cubes, positions, getPosition(), i, okDir, MapManager::EAST);
    }
    cubes.emplace_back(new Explosion(getNode()->getPosition()));
    for (const auto &position : positions) {
        cubes.emplace_back(new Explosion(position));
    }
}

void Bomb::onDeath(std::vector<std::shared_ptr<GameObject>> &cubes) {
    _owner.removeBomb(this);
    explode(cubes);
    GameObject::onDeath(cubes);
}