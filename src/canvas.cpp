/*
@name: canvas.cpp
@author: Farrrrland
@created: 2022-05-22
@modified: 2022-05-29
*/

#include "canvas.h"

Canvas::Canvas(int n, int color) : _canvas(n, std::vector<int>(n, 0)), _size(n) {
    if (color == 2) {
        _color = _2Color::Instance();
    }
    else if (color == 256) {
        _color = _256Color::Instance();
    }
}

int Canvas::GetSize() {
    return _size;
}

std::vector<std::vector<int>>* Canvas::GetCanvas() {
    return &_canvas;
}

void Canvas::SetCanvas(Coordinate coor, int color) {
    _canvas[coor.x()][coor.y()] = color;
}

int Canvas::GetGray() {
    return _gray;
}

void Canvas::SetGray(int gray) {
    _gray = gray;
}

int Canvas::GetColor() {
    return _color->GetColor(_gray);
}

bool Canvas::Plot(Coordinate coor) {
    if (coor.x() < 0 || coor.x() >= _size || coor.y() < 0 || coor.y() >= _size) {
        return false;
    }
    SetCanvas(coor, Canvas::GetColor());
    return true;
}