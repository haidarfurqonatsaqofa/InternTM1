#define _USE_MATH_DEFINES
#include "Ball.hpp"
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Konstruktor
Ball::Ball() : x(0.0), y(0.0), vx(0.0), vy(0.0) {}
Ball::Ball(double startX, double startY) : x(startX), y(startY), vx(0.0), vy(0.0) {}

// Getter
double Ball::getX() const { return x; }
double Ball::getY() const { return y; }
double Ball::getVx() const { return vx; }
double Ball::getVy() const { return vy; }

double Ball::getSpeed() const {
    return std::sqrt(vx * vx + vy * vy);
}

// Setter
void Ball::setPosition(double newX, double newY) {
    x = newX;
    y = newY;
    vx = 0.0;
    vy = 0.0;
}

// Tendangan Bola
void Ball::kick(double angleDegrees) {
    double radians = angleDegrees * (M_PI / 180.0);
    double initialSpeed = 4.0; // Naikkan kecepatan tendangan menjadi 4 m/tick
    vx = initialSpeed * std::cos(radians);
    vy = initialSpeed * std::sin(radians);
}

// Update Pergerakan & Deteksi Keluar Lapangan
void Ball::update() {
    x += vx;
    y += vy;

    double currentSpeed = getSpeed();
    if (currentSpeed > 0.0) {
        double newSpeed = currentSpeed - 1.0; // Deselerasi 1 m/tick
        if (newSpeed < 0.0) newSpeed = 0.0;

        vx = (vx / currentSpeed) * newSpeed;
        vy = (vy / currentSpeed) * newSpeed;
    }

    // Pengecekan Out Of Bounds (Batas Lapangan: X[-4.5, 4.5], Y[-3.0, 3.0])
    bool isGoalArea = (x > 4.5 && y >= -1.3 && y <= 1.3);

    if (!isGoalArea && (x < -4.5 || x > 4.5 || y < -3.0 || y > 3.0)) {
        std::cout << "\n[INFO] Bola keluar lapangan! Auto-respawn ke koordinat (0.0, 0.0).\n";
        setPosition(0.0, 0.0);
    }
}