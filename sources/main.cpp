#include "Menu.hpp"
#include "Exception.hpp"
#include <iostream>

int main()
{
    try {
        Menu menu;
    } catch (const IndieException &e) {
        std::cerr << "An error occurred in bomberman: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "A system error occurred in bomberman: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred in bomberman." << std::endl;
    }
    return 0;
}