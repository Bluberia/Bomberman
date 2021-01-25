#ifdef _WIN32
    #include <irrlicht.h>
#else
    #include <irrlicht/irrlicht.h>
#endif

#include "ECS/World.hpp"
#include "Systems/ExampleSystem.hpp"
#include "ExampleEntity.hpp"

#include "IrrlichtDevice.hpp"

int main2(void)
{
    IrrlichtDevice irrlicht(false);

    /*
    ** INITIALISATION
    */

    irr::scene::IAnimatedMesh* meshBomberman = irrlicht.loadMesh("resources/models/Character/Bomberman.MD3");
    std::vector<irr::io::path> path{"resources/models/Character/WhiteBombermanTextures.png", "resources/metal.jpg"};
    std::vector<irr::scene::IAnimatedMeshSceneNode*> models;
    std::vector<irr::scene::ISceneNode*> cubes;

    /*
    ** CREATION DES MESH
    */

    models.push_back(irrlicht.loadSceneNode(meshBomberman));
    cubes.push_back(irrlicht.loadCube());

    /*
    ** CUBE
    */

    irrlicht.loadTextureCube(path[1], cubes[0], false);
    cubes[0]->setScale(irr::core::vector3df(0.7f, 0.7f, 0.7f));

    /*
    ** BOMBERMAN
    */

    irrlicht.loadTextureModels(path[0], models[0], false);
    irrlicht.loadAnimation(irr::core::vector2di(27,76), 20, models[0]);
    models[0]->setScale(irr::core::vector3df(6, 6, 6));
    models[0]->setPosition(irr::core::vector3df(0,0,30));

    /*
    ** CAMERA
    */

    irrlicht.loadCamera(irr::core::vector3df(-100, 60, 0), irr::core::vector3df(0,0,0), \
irr::core::vector3df(0, -20, 0));


    irrlicht._smgr->drawAll();
    while (irrlicht._device->run()) {
        irrlicht.drawWindow();
    }
    return 0;
}
