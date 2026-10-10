#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "Field.hpp"
#include "Ball.hpp"
#include "Utils.hpp"
#include <optional>

enum class RobotAction {
    NONE,
    KICK,
    MOVE
};

class Robot {
protected:
    double x;
    double y;
    double heading;
    RobotAction nextAction;
    std::optional<Utils::Vector2D> perceivedBallPos;

public:
    Robot(double startX = 0.0, double startY = 0.0, double startHeading = 0.0)
        : x(startX), y(startY), heading(startHeading), nextAction(RobotAction::NONE) {}

    virtual ~Robot() = default;

    virtual void sense(const Ball& ball) = 0;
    virtual void think() = 0;
    virtual void act(Field& field, Ball& ball);

    // Helper Methods
    bool hasPerceivedBall() const { return perceivedBallPos.has_value(); }
    Utils::Vector2D getPerceivedBallPos() const { return perceivedBallPos.value_or(Utils::Vector2D{0.0, 0.0}); }

    // Getters & Setters
    double getX() const { return x; }
    double getY() const { return y; }
    double getHeading() const { return heading; }

    void setPosition(double newX, double newY) { x = newX; y = newY; }
    void setHeading(double newHeading) { heading = Utils::normalizeAngle(newHeading); }
    void setNextAction(RobotAction action) { nextAction = action; }
};

#endif // ROBOT_HPP