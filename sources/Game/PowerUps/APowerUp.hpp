#ifndef INDIE_STUDIO_APOWERUP_HPP
#define INDIE_STUDIO_APOWERUP_HPP

#include "Cube.hpp"

class APowerUp : public Cube {
protected:
    explicit APowerUp(std::string texture, irr::core::vector3df position);
public:
    void onOverlap(GameObject &player) override;
    void update(std::vector<std::shared_ptr<GameObject>> &cubes) override;
private:
};

#else

class APowerUp;

#endif