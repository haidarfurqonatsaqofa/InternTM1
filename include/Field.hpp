#ifndef FIELD_HPP
#define FIELD_HPP

class Field {
private:
    const double minX = -4.5;
    const double maxX = 4.5;
    const double minY = -3.0;
    const double maxY = 3.0;

    // Batas gawang lawan
    const double goalX = 4.5;
    const double goalMinY = -1.5;
    const double goalMaxY = 1.5;

public:
    Field() = default;

    // Memeriksa apakah koordinat (x, y) berada di dalam area lapangan
    bool isInside(double x, double y) const;

    // Memeriksa apakah bola masuk ke area gawang lawan
    bool isGoal(double x, double y) const;

    // Getter batas lapangan
    double getMinX() const { return minX; }
    double getMaxX() const { return maxX; }
    double getMinY() const { return minY; }
    double getMaxY() const { return maxY; }
};

#endif // FIELD_HPP