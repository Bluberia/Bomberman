#include "Background.hpp"

Background::Background() : Wall("sky") {
    _defaultPosition = {14,-20,0};
    _defaultScale = {20,1,40};
    createObject();
}
