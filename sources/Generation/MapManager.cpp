/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** No file there , just an Epitech header example
*/

#include <cmath>
#include <iostream>
#include <memory>
#include <Unbreakable.hpp>
#include <Breakable.hpp>
#include "MapManager.hpp"
#include "Wall/Wall.hpp"

const float MapManager::TILE_SIZE = 10.f;

const unsigned int MapManager::THRESHOLD = 100;

Vector3D<float> MapManager::lastScale(0);

MapManager::MapManager()
    : m_pn(),
      m_boxScale(1),
      m_centerPos(0),
      m_dim(13, 11)
{
    lastScale = m_boxScale;
}

MapManager::MapManager(unsigned int p_seed) : m_pn(p_seed),
                                              m_boxScale(1),
                                              m_centerPos(0),
                                              m_dim(13, 11)
{
    lastScale = m_boxScale;
}

MapManager::~MapManager()
{
}

const Vector2D<int> &MapManager::getDim() const
{
    return m_dim;
}

void MapManager::setDim(const Vector2D<int> &dim)
{
    m_dim = dim;
}

const Vector3D<float> &MapManager::getCenterPos() const
{
    return m_centerPos;
}

void MapManager::setCenterPos(const Vector3D<float> &centerPos)
{
    m_centerPos = centerPos;
}

const Vector3D<float> &MapManager::getBoxScale() const
{
    return m_boxScale;
}

void MapManager::setBoxScale(const Vector3D<float> &boxScale)
{
    m_boxScale = boxScale;
    lastScale = m_boxScale;
}

static bool isSpawnProtected(Vector2D<int> &p_dim, int ind)
{
    int corners[4] = {0, p_dim.x - 1, p_dim.x * (p_dim.y - 1), p_dim.x * p_dim.y - 1};

    for (auto cor : corners) {
        if (ind == cor || ind == cor + p_dim
            .x || ind == cor - p_dim
            .x || ind == cor + 1 || ind == cor - 1) {
            return true;
        }
    }
    return false;
}

static bool isNonDestructible(Vector2D<int> &p_dim, int ind)
{
    int x = (ind % p_dim.x) + 1;
    int y = (ind / p_dim.x) + 1;

    return !(x % 2) && !(y % 2);
}

void MapManager::generateWorld(std::vector<std::shared_ptr<GameObject>> &p_vec)
{
    double x, y;
    Vector3D<float> pos(0), rot(0);

    for (int i = 0; i < m_dim.x + 2; ++i) {
        pos.z = (m_centerPos.x - ((m_dim.x + 2) * m_boxScale.x * TILE_SIZE / 2.f)) +
                ((i % (m_dim.x + 2)) * m_boxScale.x * TILE_SIZE);
        pos.x = (m_centerPos.z - ((m_dim.y + 2) * m_boxScale.z * TILE_SIZE / 2.f));
        p_vec.push_back(std::make_shared<Unbreakable>(pos, rot, m_boxScale));
        pos.x = (m_centerPos.z + ((m_dim.y) * m_boxScale.z * 10.f / 2.f));
        p_vec.push_back(std::make_shared<Unbreakable>(pos, rot, m_boxScale));
    }
    for (int i = 0; i < m_dim.y * 2; ++i) {
        pos.z = (m_centerPos.x - ((m_dim.x + 2) * m_boxScale.x * TILE_SIZE / 2.f)) +
                ((i % 2) ? 0 : m_dim.x + 1) * m_boxScale.x * TILE_SIZE;
        pos.x =
            (m_centerPos.z - ((m_dim.y) * m_boxScale.z * TILE_SIZE / 2.f)) + (int(i / 2) * m_boxScale.z * TILE_SIZE);
        p_vec.push_back(std::make_shared<Unbreakable>(pos, rot, m_boxScale));
    }
    for (auto i = 0; i < m_dim.x * m_dim.y; i++) {
        pos.z =
            (m_centerPos.x - (m_dim.x * m_boxScale.x * TILE_SIZE / 2.f)) + ((i % m_dim.x) * m_boxScale.x * TILE_SIZE);
        pos.x = (m_centerPos.z - (m_dim.y * m_boxScale.z * TILE_SIZE / 2.f)) +
                (int(i / m_dim.x) * m_boxScale.z * TILE_SIZE);
        if (isSpawnProtected(m_dim, i)) {
            continue;
        } else if (isNonDestructible(m_dim, i)) {
            p_vec.push_back(std::make_shared<Unbreakable>(pos, rot, m_boxScale));
        } else {
            x = (double)(i % m_dim.x) / ((double)m_dim.x);
            y = (double)(i / m_dim.x) / ((double)m_dim.y);
            x = m_pn.noise(x * 10, y * 10, .8f);
            if (THRESHOLD <= floor(255 * x)) {
                p_vec.push_back(std::make_shared<Breakable>(pos, rot, m_boxScale));
            }
        }
    }
}

void MapManager::setWorldSeed(unsigned int p_seed)
{
    m_pn.setSeed(p_seed);
}

Vector3D<float> MapManager::getLeftUpperCorner() const
{
    return {
        m_centerPos.z + ((m_dim.y - 2) * m_boxScale.z * TILE_SIZE) / 2,
        0,
        m_centerPos.x + ((m_dim.x - 2) * m_boxScale.x * TILE_SIZE) / 2};
}

Vector3D<float> MapManager::getRightUpperCorner() const
{
    return {
        m_centerPos.z + ((m_dim.y - 2) * m_boxScale.z * TILE_SIZE) / 2,
        0,
        m_centerPos.x - (m_dim.x * m_boxScale.x * TILE_SIZE) / 2};
}

Vector3D<float> MapManager::getLeftLowerCorner() const
{
    return {
        m_centerPos.z - (m_dim.y * m_boxScale.z * TILE_SIZE) / 2,
        0,
        m_centerPos.x + ((m_dim.x - 2) * m_boxScale.x * TILE_SIZE) / 2};
}

Vector3D<float> MapManager::getRightLowerCorner() const
{
    return {
        m_centerPos.z - (m_dim.y * m_boxScale.z * TILE_SIZE) / 2,
        0,
        m_centerPos.x - (m_dim.x * m_boxScale.x * TILE_SIZE) / 2};
}

Vector3D<float> MapManager::evaluateTiledPosition(const Vector3D<float> &p_position)
{
    auto x = std::floor(p_position.x / 10.f) * 10.f + TILE_SIZE / 2.f;
    auto z = std::floor(p_position.z / 10.f) * 10.f + TILE_SIZE / 2.f;

    return {x, 0, z};
}

irr::core::vector3df MapManager::evaluateTiledPosition(const irr::core::vector3df &p_position)
{
    Vector3D<float> vec = MapManager::evaluateTiledPosition(Vector3D<float>{p_position.X, p_position.Y, p_position.Z});
    return {vec.x, vec.y, vec.z};
}

MapManager::ECardinal MapManager::isInRange(
    const irr::core::vector3df &p_p1,
    const irr::core::vector3df &p_p2,
    int p_range
)
{
    int range = static_cast<int>(p_range * lastScale.x * TILE_SIZE);
    bool xSame = p_p1.X == p_p2.X;
    bool zSame = p_p1.Z == p_p2.Z;
    bool xWest = (p_p1.X + range == p_p2.X);
    bool xEast = (p_p1.X - range == p_p2.X);
    bool xRange = xWest || xEast;
    bool zNorth = (p_p1.Z + range == p_p2.Z);
    bool zSouth = (p_p1.Z - range == p_p2.Z);
    bool zRange = zNorth || zSouth;

    if (!((xRange && zSame) ^ (zRange && xSame)))
        return NONE;
    if (zRange) {
        return zNorth ? NORTH : SOUTH;
    } else {
        return xWest ? WEST : EAST;
    }
}

irr::core::vector3df MapManager::getPosAtDirAndRange(const irr::core::vector3df &p_position, ECardinal dir, int p_range)
{
    p_range *= int(lastScale.x * TILE_SIZE);
    switch (dir) {
    case NORTH:
        return irr::core::vector3df(p_position.X, p_position.Y, p_position.Z + p_range);
    case WEST:
        return irr::core::vector3df(p_position.X + p_range, p_position.Y, p_position.Z);
    case SOUTH:
        return irr::core::vector3df(p_position.X, p_position.Y, p_position.Z - p_range);
    case EAST:
        return irr::core::vector3df(p_position.X - p_range, p_position.Y, p_position.Z);
    default:
    case NONE:
        return irr::core::vector3df();
    }
}
