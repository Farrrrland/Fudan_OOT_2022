#include "../include/canvas.h"

void Canvas::setData(Coordinate coor, int val) {
    _canvas[coor.x()][coor.y()] = val;
}
std::vector<std::vector<int>> Canvas::getData() {
    return _canvas;
}