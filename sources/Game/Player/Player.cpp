#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "Player.hpp"
#include "IrrlichtDevice.hpp"
#include "GameObject.hpp"
#include "Model.hpp"

void Player::update(std::vector<std::shared_ptr<GameObject>> &cubes) {
    if (!_alive)
        return;
    APlayer::update(cubes);
    auto& eventReceiver = IrrlichtDevice::getInstance()._receiver;
    bool event = false;
    static bool placebomb = false;

    if (eventReceiver.IsKeyDown(_keys[UP])) {
        moveUp();
        setAnimation("walk");
        event = true;
    }
    if (eventReceiver.IsKeyDown(_keys[DOWN])) {
        moveDown();
        setAnimation("walk");
        event = true;
    }
    if (eventReceiver.IsKeyDown(_keys[LEFT])) {
        moveLeft();
        setAnimation("walk");
        event = true;
    }
    if (eventReceiver.IsKeyDown(_keys[RIGHT])) {
        moveRight();
        setAnimation("walk");
        event = true;
    }
    if (!placebomb && eventReceiver.IsKeyDown(_keys[BOMB])) {
        placebomb = true;
        placeBomb(cubes);
    } else if (!eventReceiver.IsKeyDown(_keys[BOMB])) {
        placebomb = false;
    }
    if (!event)
        setAnimation("idle");
}

bool Player::isABot() {
    return false;
}

Player::Player(int id) :
    APlayer(id),
    _keys({ irr::KEY_KEY_Z, irr::KEY_KEY_Q, irr::KEY_KEY_S, irr::KEY_KEY_D, irr::KEY_SPACE }) {
}

const std::array<irr::EKEY_CODE, 5> & Player::getKeys() const {
    return _keys;
}

void Player::setKeys(const std::array<irr::EKEY_CODE, 5> & keys) {
    _keys = keys;
}
