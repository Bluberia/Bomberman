#ifndef INDIE_STUDIO_MODEL_HPP
#define INDIE_STUDIO_MODEL_HPP

#include <map>
#include <vector>
#include <utility>
#include <memory>
#include "GameObject.hpp"

class Model : public GameObject {
protected:
    explicit Model(std::string model, std::string texture);
    void createObject();
    void addAnimation(const std::string &name, int start, int end, int speed);
    void setAnimation(const std::string &name);
private:
    void loadModel();
    void loadTexture();
protected:
    std::string _model;
    std::string _texture;
private:
    std::string _currentAnimation;
    std::map<std::string, irr::core::vector3di> _animations;
};

#else

class Model;

#endif