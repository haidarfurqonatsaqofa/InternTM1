#ifndef BALL_HPP
#define BALL_HPP

class Ball {
private:
    double x;
    double y;
    double vx;
    double vy;

public:
    Ball();
    Ball(double startX, double startY);

    // Getter
    double getX() const;
    double getY() const;
    double getVx() const;
    double getVy() const;
    double getSpeed() const;

    // Setter & Method
    void setPosition(double newX, double newY);
    void kick(double angleDegrees);
    void update();
};

#endif // BALL_HPP