/*
@name: canvas.h
@author: Farrrrland
@created: 2022-05-22
@modified: 2022-05-29
*/

#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <memory>
#include <vector>
#include "color.h"
#include "coordinate.hpp"

class Canvas {
public:
    Canvas(int n, int color);
    // getter & setter
    int GetSize();
    std::vector<std::vector<int>>* GetCanvas();
    void SetCanvas(Coordinate coor, int color);
    int GetGray();
    void SetGray(int gray);
    int GetColor();
    bool Plot(Coordinate coor);
private:
    std::vector<std::vector<int>> _canvas;
    int _size;
    int _gray = 0;
    std::shared_ptr<Color> _color;
};

#endif