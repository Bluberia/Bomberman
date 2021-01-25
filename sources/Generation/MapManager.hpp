/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** No file there , just an Epitech header example
*/

#ifndef INDIE_STUDIO_MAPGENERATOR_HPP
#define INDIE_STUDIO_MAPGENERATOR_HPP

#include <memory>
#include "PerlinNoise.hpp"
#include "Vector3D.hpp"
#include "GameObject.hpp"

class MapManager
{
public:
    static const float TILE_SIZE;

    static const unsigned int THRESHOLD;

    typedef enum
    {
        NONE = 0b1111,
        NORTH = 0b0111,
        WEST = 0b1011,
        SOUTH = 0b1101,
        EAST = 0b1110
    } ECardinal;

    MapManager();
    explicit MapManager(unsigned int p_seed);
    virtual ~MapManager();

    const Vector2D<int> &getDim() const;
    const Vector3D<float> &getCenterPos() const;
    const Vector3D<float> &getBoxScale() const;

    void setDim(const Vector2D<int> &dim);
    void setCenterPos(const Vector3D<float> &centerPos);
    void setBoxScale(const Vector3D<float> &boxScale);

    void setWorldSeed(unsigned int p_seed);

    Vector3D<float> getLeftUpperCorner() const;
    Vector3D<float> getRightUpperCorner() const;
    Vector3D<float> getLeftLowerCorner() const;
    Vector3D<float> getRightLowerCorner() const;

    void generateWorld(std::vector<std::shared_ptr<GameObject>> &p_vec);

    static Vector3D<float> evaluateTiledPosition(const Vector3D<float> &p_position);
    static irr::core::vector3df evaluateTiledPosition(const irr::core::vector3df &p_position);

    static ECardinal isInRange(const irr::core::vector3df &p_p1, const irr::core::vector3df &p_p2, int p_range);
    static irr::core::vector3df getPosAtDirAndRange(const irr::core::vector3df &p_position, ECardinal dir, int p_range);
private:
    static Vector3D<float> lastScale;

    PerlinNoise m_pn;
    Vector2D<int> m_dim;
    Vector3D<float> m_centerPos;
    Vector3D<float> m_boxScale;
};

#endif