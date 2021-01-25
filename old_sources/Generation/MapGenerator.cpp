/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** No file there , just an Epitech header example
*/

#include <cmath>
#include "MapGenerator.hpp"
#include "Box.hpp"
#include "Wall/Wall.hpp"

MapGenerator::MapGenerator() : m_pn(), m_boxScale(1), m_centerPos(0), m_dim(13, 11)
{}

MapGenerator::MapGenerator(unsigned int p_seed) : m_pn(p_seed), m_boxScale(1), m_centerPos(0), m_dim(13, 11)
{}

MapGenerator::~MapGenerator()
{}

const Vector2D<int> &MapGenerator::getDim() const
{
    return m_dim;
}

void MapGenerator::setDim(const Vector2D<int> &dim)
{
    m_dim = dim;
}

const Vector3D<float> &MapGenerator::getCenterPos() const
{
    return m_centerPos;
}

void MapGenerator::setCenterPos(const Vector3D<float> &centerPos)
{
    m_centerPos = centerPos;
}

const Vector3D<float> &MapGenerator::getBoxScale() const
{
    return m_boxScale;
}

void MapGenerator::setBoxScale(const Vector3D<float> &boxScale)
{
    m_boxScale = boxScale;
}

static bool isSpawnProtected(Vector2D<int> &p_dim, int ind)
{
    int corners[4] = {0, p_dim.x - 1, p_dim.x * (p_dim.y - 1), p_dim.x * p_dim.y - 1};

    for (auto cor : corners) {
        if (ind == cor || ind == cor + p_dim.x || ind == cor - p_dim.x || ind == cor + 1 || ind == cor - 1)
            return true;
    }
    return false;
}

static bool isNonDestructible(Vector2D<int> &p_dim, int ind)
{
    int x = (ind % p_dim.x) + 1;
    int y = (ind / p_dim.x) + 1;

    return x % 2 && y % 2;
}

void MapGenerator::generateWorld(ECS::World &p_world)
{
    double x;
    double y;
    Vector3D<float> pos(0), rot(0), scale(1);

    for (auto i = 0; i < m_dim.x * m_dim.y; i++) {
        pos.x = (m_centerPos.x - (m_dim.x / 2.f)) + ((i % m_dim.x) * m_boxScale.x);
        pos.y = (m_centerPos.z - (m_dim.y / 2.f)) + ((float(i) / m_dim.x) * m_boxScale.z);
        if (isSpawnProtected(m_dim, i)) {
            continue;
        } else if (isNonDestructible(m_dim, i)) {
            p_world.addEntity<ECS::Entities::Wall>(pos, rot, scale);
        } else {
            x = (double)(i % m_dim.x) / ((double)m_dim.x);
            y = (double)(i / m_dim.x) / ((double)m_dim.y);
            x = m_pn.noise(x * 10, y * 10, .8f);
            if (100 <= floor(255 * x)) {
                p_world.addEntity<ECS::Entities::Box>(pos, rot, scale);
            }
        }
    }
}

void MapGenerator::setWorldSeed(unsigned int p_seed)
{
    m_pn.setSeed(p_seed);
}
