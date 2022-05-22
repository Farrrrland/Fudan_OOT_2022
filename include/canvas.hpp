// 单例模式的画布
#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <memory>
#include <vector>
#include <string>
#include <iostream>
// #include "coordinate.h"


// class Canvas {
// public:
//     vector<vector<int>>* Get();
//     void Set(Coordinate coor, int color) {
//         _canvas[coor.x()][coor.y()] = color;
//     }
    
//     Canvas(int n) : _canvas(n, vector<int>(n, 0)) {}
// private:
//     vector<vector<int>> _canvas;
// };

class Canvas {
public:
    static Canvas* getInstance() {
        return singleCanvas;
    }

    std::vector<std::vector<int>> &get_data() {
        return _canvas;
    }
private:
    static Canvas* singleCanvas;
    static std::vector<std::vector<int>> _canvas;
    static const int length = 51;
    static const int width = 50;
};

class Printer
{
public:
	static void printText(std::string s) { std::cout << s << std::endl; count++; }
	static Printer* getInstance()
	{
		return singlePrinter;
	}
	static int getUseTimes()
	{
		return count;
	}

private:
	static int count;
	static Printer* singlePrinter;
	Printer() {}
	Printer(const Printer& p) {}
};

#endif