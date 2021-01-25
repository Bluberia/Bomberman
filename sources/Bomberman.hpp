/*
** EPITECH PROJECT, 2019
** Indie
** File description:
** Bomberman
*/

#ifndef INDIE_STUDIO_BOMBERMAN_HPP
#define INDIE_STUDIO_BOMBERMAN_HPP

#include <vector>
#include <string>
#include "Player.hpp"
#include "GameObject.hpp"

class Bomberman {
public:
    explicit Bomberman();
    void startGame(bool hasTwoPlayers);

    ~Bomberman();

private:
    void runGame();
    void exitGame();
    void createAssets();
    void createPlayers(int playerCount);
    void createMap();
    void setRunning(bool running);
    void checkExit();
    bool running();
    void setupCamera();

    bool _running;
    bool soloGame;
    std::vector<std::shared_ptr<GameObject>> _cubes;
    void checkEndGame();
    void victory(APlayer &player);
    void drawVictory(APlayer &player);
    void drawEquality();
    std::vector<std::shared_ptr<APlayer>> getPlayers();
    std::array<bool, 4> checkAlive(std::vector<std::shared_ptr<APlayer>>);
};

#else

class Bomberman;

#endif
