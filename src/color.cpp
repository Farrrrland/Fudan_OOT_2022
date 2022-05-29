#include "color.h"

// _2Color
std::shared_ptr<Color> _2Color::_instance;

std::shared_ptr<Color> _2Color::Instance() {
    if (!_instance) _instance = std::make_shared<_2Color>();
    return _instance;
}

int _2Color::GetColor(int color) {
    return !!color;
}

// _256Color
std::shared_ptr<Color> _256Color::_instance;

std::shared_ptr<Color> _256Color::Instance() {
    if (!_instance) _instance = std::make_shared<_256Color>();
    return _instance;
}

int _256Color::GetColor(int color) {
    return color * 10 / 256;
}