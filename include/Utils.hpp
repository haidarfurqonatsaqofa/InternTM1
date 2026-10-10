#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>

namespace Utils {

    // Struktur data sederhana untuk menyimpan koordinat 2D (meter)
    struct Vector2D {
        double x;
        double y;
    };

    // Struktur data untuk posisi sel dalam grid ASCII (baris, kolom)
    struct GridCell {
        int row;
        int col;
    };

    // Menghitung jarak Euclidean antara dua titik (x1, y1) dan (x2, y2)
    double euclideanDistance(double x1, double y1, double x2, double y2);

    // Menghitung sudut bearing (derajat) dari titik A ke titik B
    double calculateBearing(double fromX, double fromY, double toX, double toY);

    // Menormalisasi sudut agar selalu berada di rentang [-180, 180] derajat
    double normalizeAngle(double angle);

    // Mengonversi koordinat kontinu (x, y) dalam meter ke indeks (row, col) grid ASCII
    // Ukuran lapangan: x [-4.5, 4.5], y [-3.0, 3.0], 1 petak = 0.5m x 0.5m
    GridCell meterToGrid(double x, double y);

    // Mengonversi indeks (row, col) grid ASCII kembali ke koordinat tengah petak dalam meter
    Vector2D gridToMeter(int row, int col);

} // namespace Utils

#endif // UTILS_HPP