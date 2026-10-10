#define _USE_MATH_DEFINES
#include "Utils.hpp"

namespace Utils {

    double euclideanDistance(double x1, double y1, double x2, double y2) {
        double dx = x2 - x1;
        double dy = y2 - y1;
        return std::sqrt(dx * dx + dy * dy);
    }

    double calculateBearing(double fromX, double fromY, double toX, double toY) {
        double dx = toX - fromX;
        double dy = toY - fromY;
        // std::atan2 mengembalikan radian dalam range [-PI, PI]
        double radians = std::atan2(dy, dx);
        // Konversi ke derajat (1 rad = 180 / PI)
        double degrees = radians * (180.0 / M_PI);
        return normalizeAngle(degrees);
    }

    double normalizeAngle(double angle) {
        while (angle > 180.0)  angle -= 360.0;
        while (angle <= -180.0) angle += 360.0;
        return angle;
    }

    GridCell meterToGrid(double x, double y) {
        // Batas lapangan:
        // x: [-4.5, 4.5] -> total 18 petak (lebar) + titik tengah -> 19 kolom (0 - 18)
        // y: [-3.0, 3.0] -> total 12 petak (tinggi) + titik tengah -> 13 baris (0 - 12)
        // Petak atas (y = 3.0) adalah baris 0, petak kiri (x = -4.5) adalah kolom 0.
        
        int col = static_cast<int>(std::round((x + 4.5) / 0.5));
        int row = static_cast<int>(std::round((3.0 - y) / 0.5));

        return {row, col};
    }

    Vector2D gridToMeter(int row, int col) {
        double x = (col * 0.5) - 4.5;
        double y = 3.0 - (row * 0.5);
        return {x, y};
    }

} // namespace Utils