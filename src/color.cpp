/*
@name: color.cpp
@author: Farrrrland
@created: 2022-05-25
@modified: 2022-05-29
*/

#include "color.h"

// black & white
std::shared_ptr<Color> _2Color::_instance;

std::shared_ptr<Color> _2Color::Instance() {
    return !_instance ? std::make_shared<_2Color>() : _instance;
}

int _2Color::GetColor(int color) {
    return !!color;
}

// 256 gray level color
std::shared_ptr<Color> _256Color::_instance;

std::shared_ptr<Color> _256Color::Instance() {
    return !_instance ? std::make_shared<_256Color>() : _instance;
}

int _256Color::GetColor(int color) {
    return color * 10 / 256;
}