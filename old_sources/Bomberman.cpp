/*
** EPITECH PROJECT, 2019
** Indie
** File description:
** Bomberman
*/

#include "Bomberman.hpp"
#include "IrrlichtDevice.hpp"

Bomberman::Bomberman(std::vector<std::string> arguments) : _enableDriverChoice(false)
{
    for (auto &i : arguments) {
        if (i == "--driver" || i == "-d")
            _enableDriverChoice = true;
    }
}

void Bomberman::run()
{
}
