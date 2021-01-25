#include <random>
#include "Bot.hpp"

Bot::Bot(int id) :
        APlayer(id) {
    _position = getNode()->getPosition();
    it = 0;
}

bool Bot::isABot() {
    return false;
}

void Bot::update(std::vector<std::shared_ptr<GameObject>> &cubes) {
    if (!_alive)
        return;
    APlayer::update(cubes);
    std::random_device engine;
    std::uniform_int_distribution<int> distribution(1, 4);

    irr::core::vector3df pos = getNode()->getPosition();

    switch (it) {
    case 1:
        moveUp();
        break;
    case 2:
        moveDown();
        break;
    case 3:
        moveRight();
        break;
    case 4:
        moveLeft();
        break;
    }
    if (pos.X == _position.X && pos.Y == _position.Y && pos.Z == _position.Z) {
        it = distribution(engine);
        placeBomb(cubes);
    }
    _position.X = pos.X;
    _position.Y = pos.Y;
    _position.Z = pos.Z;
}

