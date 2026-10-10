#include "Field.hpp"

bool Field::isInside(double x, double y) const {
    return (x >= minX && x <= maxX && y >= minY && y <= maxY);
}

bool Field::isGoal(double x, double y) const {
    // Bola dianggap gol jika melewati garis x = 4.5m pada rentang y gawang [-1.5, 1.5]
    return (x >= goalX && y >= goalMinY && y <= goalMaxY);
}