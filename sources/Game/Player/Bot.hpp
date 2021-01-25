#ifndef INDIE_STUDIO_BOT_HPP
#define INDIE_STUDIO_BOT_HPP

#include "APlayer.hpp"
#include <functional>

class Bot : public APlayer {
public:
    Bot(int id);
    bool isABot() override;
    void update(std::vector<std::shared_ptr<GameObject>> &cubes) override;

private:
    irr::core::vector3df _position;
    int it;
};

#else

class Bot;

#endif
