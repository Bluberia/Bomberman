#ifndef INDIE_STUDIO_WALL_HPP
#define INDIE_STUDIO_WALL_HPP

#include "Cube.hpp"

class Wall : public Cube {
public:
    Wall(std::string texture);
    Wall(std::string texture, Vector3D<float> &p_pos, Vector3D<float> &p_rot, Vector3D<float> &p_sca);

    void breakWall(std::vector<std::shared_ptr<GameObject>> &cubes);
    virtual bool isBreakable();
};

#else

class Wall;

#endif