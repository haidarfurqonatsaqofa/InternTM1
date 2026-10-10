#define _USE_MATH_DEFINES
#include "Camera.hpp"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

bool Camera::isPointInVisionTriangle(double pointX, double pointY, double robotX, double robotY, double robotHeading) const {
    double dx = pointX - robotX;
    double dy = pointY - robotY;

    // Transformasi koordinat global ke koordinat lokal robot berbasis heading (8 arah)
    double rad = -robotHeading * (M_PI / 180.0);
    double localX = dx * std::cos(rad) - dy * std::sin(rad); // Jarak lurus ke depan robot
    double localY = dx * std::sin(rad) + dy * std::cos(rad); // Jarak menyamping dari robot

    // Jangkauan depan segitiga pandang: 0 s/d 1.5 meter
    if (localX < 0.0 || localX > 1.5) {
        return false;
    }

    // Lebar alas segitiga = 3.5m pada jarak 1.5m
    double halfBaseAtX = (localX / 1.5) * (3.5 / 2.0);

    return (std::abs(localY) <= halfBaseAtX);
}

std::optional<Utils::Vector2D> Camera::scanBall(const Ball& ball, double robotX, double robotY, double robotHeading) const {
    if (isPointInVisionTriangle(ball.getX(), ball.getY(), robotX, robotY, robotHeading)) {
        return Utils::Vector2D{ball.getX(), ball.getY()};
    }
    return std::nullopt;
}