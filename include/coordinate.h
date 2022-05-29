#ifndef COORDINATE_H
#define COORDINATE_H
  
class Coordinate {
public:
    int x() { return _x; }
    int y() { return _y; }
    Coordinate(int x, int y) : _x(x), _y(y) {}
    Coordinate operator + (Coordinate A) const {
        return Coordinate(_x + A.x(), _y + A.y());
    }
private:
    int _x, _y;
};

#endif