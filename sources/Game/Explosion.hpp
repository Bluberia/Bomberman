#ifndef INDIE_STUDIO_EXPLOSION_HPP
#define INDIE_STUDIO_EXPLOSION_HPP

#include "Cube.hpp"

class Explosion : public Cube {
protected:
    void onOverlap(GameObject &player) override;
    void onCollide() override;
//    void createObject() override;
public:
    static const double EXPLOSION_PERSISTENCE_TIME;

    Explosion(const irr::core::vector3df &position);
    virtual ~Explosion();

    void update(std::vector<std::shared_ptr<GameObject>>& cubes);

    void onDeath(std::vector<std::shared_ptr<GameObject>> &cubes) override;
};

#else

class Explosion;

#endif
