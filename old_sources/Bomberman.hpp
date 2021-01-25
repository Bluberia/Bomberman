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

class Bomberman {
public:
    explicit Bomberman(std::vector<std::string> arguments = {});
    void run();

private:
    bool _enableDriverChoice;
};

#endif
