// Singleton Mode Canvas
#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <vector>
#include <iostream>
#include "coordinate.h"
 
class Canvas {
public:
	static Canvas* getInstance() {
        static Canvas canvas;
        if (canvas._canvas.empty()) {
            canvas._canvas = std::vector<std::vector<int>>(_length, std::vector<int>(_width, 0));
        }
        return &canvas;
    }
    void setData(Coordinate coor, int val);
    std::vector<std::vector<int>> getData();
private:
	Canvas(){};
	Canvas(const Canvas&);
	Canvas& operator==(const Canvas&);
    static const int _length = 5;
    static const int _width = 5;
    std::vector<std::vector<int>> _canvas;
};

#endif