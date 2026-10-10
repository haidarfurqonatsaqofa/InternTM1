#ifndef STRIKER_HPP
#define STRIKER_HPP

#include "Robot.hpp"
#include "State.hpp"
#include "Camera.hpp"
#include "Ball.hpp"
#include <memory>
#include <string>

class State;

class Striker : public Robot {
private:
    std::unique_ptr<State> currentState;
    Camera camera;

public:
    Striker();
    Striker(double startX, double startY, double startHeading = 0.0);
    ~Striker() override = default;

    void sense(const Ball& ball) override;
    void think() override;

    void changeState(State* newState);
    State* getCurrentState() const;
    std::string getCurrentStateName() const;
};

#endif // STRIKER_HPP