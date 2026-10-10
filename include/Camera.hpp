#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Utils.hpp"
#include "Ball.hpp"
#include <optional>

class Camera {
public:
    Camera() = default;

    // Memeriksa apakah suatu koordinat (x, y) berada dalam segitiga pandang robot
    bool isPointInVisionTriangle(double pointX, double pointY, double robotX, double robotY, double robotHeading) const;

    // Memindai bola: mengembalikan posisi bola jika berada di area pandang, nullopt jika tidak terlihat
    std::optional<Utils::Vector2D> scanBall(const Ball& ball, double robotX, double robotY, double robotHeading) const;
};

#endif // CAMERA_HPP