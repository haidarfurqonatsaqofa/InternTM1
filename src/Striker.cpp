#include "Striker.hpp"
#include "State.hpp"
#include <typeinfo>

Striker::Striker() 
    : Robot(0.0, 0.0, 0.0), currentState(std::make_unique<SearchState>()) {}

Striker::Striker(double startX, double startY, double startHeading)
    : Robot(startX, startY, startHeading), currentState(std::make_unique<SearchState>()) {}

void Striker::sense(const Ball& ball) {
    auto ballVision = camera.scanBall(ball, x, y, heading);
    
    if (ballVision.has_value()) {
        perceivedBallPos = ballVision;
    } else {
        perceivedBallPos = std::nullopt;
    }
}

void Striker::think() {
    if (currentState) {
        currentState->execute(this);
    }
}

void Striker::changeState(State* newState) {
    if (newState) {
        currentState.reset(newState);
    }
}

State* Striker::getCurrentState() const {
    return currentState.get();
}

std::string Striker::getCurrentStateName() const {
    if (!currentState) return "UNKNOWN";
    if (dynamic_cast<SearchState*>(currentState.get())) return "SEARCH_BALL";
    if (dynamic_cast<ApproachState*>(currentState.get())) return "APPROACH_BALL";
    if (dynamic_cast<AlignState*>(currentState.get())) return "ALIGN_GOAL";
    if (dynamic_cast<KickState*>(currentState.get())) return "KICK";
    return "UNKNOWN";
}