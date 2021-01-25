#ifndef INDIE_STUDIO_APLAYER_HPP
#define INDIE_STUDIO_APLAYER_HPP

#include <vector>
#include <memory>
#include "Model.hpp"
#include "Bomb.hpp"

class APlayer : public Model {
public:
    APlayer(int id);
    virtual ~APlayer();
    virtual void update(std::vector<std::shared_ptr<GameObject>> &cubes) override;

    //Methods
public:
    void kill();
    virtual bool isABot() = 0;
    void removeBomb(GameObject *bomb);
    const int getPlayerId() const;

    float getSpeed() const;
    void setSpeed(float speed);

    int getBombPower() const;
    void setBombPower(int bombPower);

    void setMaxBombCount(int maxBombCount);
    int getMaxBombCount() const;

    bool canWallPass() const;
    void setWallPass(bool wallPass);
protected:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void placeBomb(std::vector<std::shared_ptr<GameObject>> &cubes);

protected:

    //Attributes
protected:
    bool _alive;
public:
    bool isAlive() const;
    void setPosition(const irr::core::vector3df &position) override;
private:
    const int _playerId;
    float _speed;
    int _bombPower;
    int _maxBombCount;
    bool _wallPass;

    std::vector<std::shared_ptr<Bomb>> _bombs;
};

#else

class APlayer;

#endif
