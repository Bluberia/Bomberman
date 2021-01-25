/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** No file there , just an Epitech header example
*/

#ifndef INDIE_STUDIO_MAPGENERATOR_HPP
#define INDIE_STUDIO_MAPGENERATOR_HPP


#include "PerlinNoise.hpp"
#include "Vector3D.hpp"
#include "World.hpp"

class MapGenerator
{
public:
    MapGenerator();
    explicit MapGenerator(unsigned int p_seed);
    virtual ~MapGenerator();

    const Vector2D<int> &getDim() const;
    const Vector3D<float> &getCenterPos() const;
    const Vector3D<float> &getBoxScale() const;

    void setDim(const Vector2D<int> &dim);
    void setCenterPos(const Vector3D<float> &centerPos);
    void setBoxScale(const Vector3D<float> &boxScale);

    void setWorldSeed(unsigned int p_seed);

    void generateWorld(ECS::World &p_world);
private:
    PerlinNoise m_pn;
    Vector2D<int> m_dim;
    Vector3D<float> m_centerPos;
    Vector3D<float> m_boxScale;
};


#endif //INDIE_STUDIO_MAPGENERATOR_HPP
