#ifndef INDIE_STUDIO_BOMB_HPP
#define INDIE_STUDIO_BOMB_HPP

#include "Model.hpp"
#include "APlayer.hpp"

class Bomb : public Model {
public:
    static const double INITIAL_LIFESPAN;

    Bomb(APlayer &p_player, int p_range, const irr::core::vector3df& p_pos);

    int _range;
    APlayer &_owner;
    void explode(std::vector<std::shared_ptr<GameObject>> &cubes);
    void onDeath(std::vector<std::shared_ptr<GameObject>> &cubes) override;

private:
};

#else

class Bomb;

#endif
