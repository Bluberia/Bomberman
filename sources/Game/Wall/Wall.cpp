#include <random>
#include "BombUp.hpp"
#include "FireUp.hpp"
#include "SpeedUp.hpp"
#include "WallPass.hpp"
#include "Wall.hpp"
#include "IrrlichtDevice.hpp"

Wall::Wall(std::string texture) :
    Cube(texture)
{
    solid = true;
    _type = UNBREAKABLE;
    createObject();
}

Wall::Wall(std::string texture, Vector3D<float> &p_pos, Vector3D<float> &p_rot, Vector3D<float> &p_sca) :
        Wall(texture)
{
    _defaultPosition = {p_pos.x, p_pos.y, p_pos.z};
    _defaultRotation = {p_rot.x, p_rot.y, p_rot.z};
    _defaultScale = {p_sca.x, p_sca.y, p_sca.z};
    createObject();
    addCollision();
}

void Wall::breakWall(std::vector<std::shared_ptr<GameObject>> &cubes) {
    std::random_device engine;
    std::uniform_int_distribution<int> distribution(1, 10);

    switch (distribution(engine)) {
        case 1:
            cubes.emplace_back(new BombUp(getPosition()));
            break;
        case 2:
            cubes.emplace_back(new FireUp(getPosition()));
            break;
        case 3:
            cubes.emplace_back(new SpeedUp(getPosition()));
            break;
        case 4:
            cubes.emplace_back(new WallPass(getPosition()));
            break;
        default:break;
    }
    setDeleted(true);
}

bool Wall::isBreakable()
{
    return false;
}
