/*
@name: coordinate.hpp
@author: Farrrrland
@created: 2022-05-22
@modified: 2022-05-29
*/

#ifndef _COORDINATE_HPP_
#define _COORDINATE_HPP_

class Coordinate {
public:
    int x() { 
        return _x; 
    }
    int y() { 
        return _y; 
    }
    Coordinate(int x, int y) : _x(x), _y(y) {}
    Coordinate operator + (Coordinate coor) const {
        return Coordinate(_x + coor.x(), _y + coor.y());
    }
private:
    int _x, _y;
};

#endif