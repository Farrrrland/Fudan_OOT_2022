#include "board.h"

Board::Board(int n, int color) : _canvas(n), _size(n) {
    if (color == 2) _color = _2Color::Instance();
    else if (color == 256) _color = _256Color::Instance();
}

int Board::GetSize() {
    return _size;
}

std::vector<std::vector<int>>* Board::GetCanvas() {
    return _canvas.Get();
}

int Board::GetGray() {
    return _gray;
}

void Board::SetGray(int gray) {
    _gray = gray;
}

int Board::GetColor() {
    return _color->GetColor(_gray);
}

bool Board::Plot(Coordinate coor) {
    if (coor.x() < 0 || coor.x() >= _size || coor.y() < 0 || coor.y() >= _size) return false;
    _canvas.Set(coor, Board::GetColor());
    return true;
}