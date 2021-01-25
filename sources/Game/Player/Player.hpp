#ifndef INDIE_STUDIO_PLAYER_HPP
#define INDIE_STUDIO_PLAYER_HPP

#include <vector>
#include <memory>
#include <utility>
#include "APlayer.hpp"
#include "Bomb.hpp"

class Player : public APlayer {
public:
    Player(int id);
    void update(std::vector<std::shared_ptr<GameObject>> &cubes) override;
    bool isABot() override;

    const std::array<irr::EKEY_CODE, 5> &getKeys() const;
    void setKeys(const std::array<irr::EKEY_CODE, 5> &keys);
    
private:
    enum {
        UP = 0,
        LEFT = 1,
        DOWN = 2,
        RIGHT = 3,
        BOMB = 4
    };
    std::array<irr::EKEY_CODE, 5> _keys;
};

#else

class Player;

#endif
