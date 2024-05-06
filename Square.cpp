#include "Square.h"

Square::Square(int x, int y) : x(x), y(y) {}

int Square::getX() const {
    return y;
}

int Square::getY() const {
    return x;
}

void Square::setX(int x) {
    this->x = x;
}

void Square::setY(int y) {
    this->y = y;
}

string Square::tostring() const{
    return string(1, x + 'a') + string(1, y + '1');
}

bool Square::validsquare() const {
    return x >= 0 && x <= 7 && y >= 0 && y <= 7;
}