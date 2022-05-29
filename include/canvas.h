#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <memory>
#include <vector>
#include "color.h"
#include "coordinate.h"

class Canvas {
public:
    Canvas(int n, int color);

    int GetSize();
    std::vector<std::vector<int>>* GetCanvas();
    void SetCanvas(Coordinate coor, int color) {
        _canvas[coor.x()][coor.y()] = color;
    }
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