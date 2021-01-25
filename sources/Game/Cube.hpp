#ifndef INDIE_STUDIO_CUBE_HPP
#define INDIE_STUDIO_CUBE_HPP

#include "GameObject.hpp"

class Cube : public GameObject {
public:
    explicit Cube(std::string texture, double lifespan = -1);
protected:
    void createObject();
private:
    void loadTexture();

protected:
    const std::string _texture;
};

#else

class Cube;

#endif