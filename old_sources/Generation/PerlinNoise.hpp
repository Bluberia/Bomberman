/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** No file there , just an Epitech header example
*/

#ifndef INDIE_STUDIO_PERLINNOISE_HPP
#define INDIE_STUDIO_PERLINNOISE_HPP

#include <vector>

class PerlinNoise
{
public:
    PerlinNoise();
    explicit PerlinNoise(unsigned int p_seed);
    ~PerlinNoise();

    void setSeed(unsigned int p_seed);
    double noise(double x, double y, double z);
private:
    double lerp(double t, double a, double b);
    double fade(double t);
    double grad(int hash, double x, double y, double z);

    std::vector<int> m_p;
};




#endif //INDIE_STUDIO_PERLINNOISE_HPP
