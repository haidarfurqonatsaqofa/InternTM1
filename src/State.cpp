#define _USE_MATH_DEFINES
#include "../include/State.hpp"
#include "../include/Striker.hpp"
#include "../include/Utils.hpp"
#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Helper pembulatan sudut ke 4 arah mata angin (0, 90, 180, -90)
static double snapTo4Directions(double angle) {
    double norm = Utils::normalizeAngle(angle);
    if (norm >= -45.0 && norm < 45.0) return 0.0;        // Kanan (0 deg)
    if (norm >= 45.0 && norm < 135.0) return 90.0;      // Atas (90 deg)
    if (norm >= -135.0 && norm < -45.0) return -90.0;   // Bawah (-90 deg)
    return 180.0;                                       // Kiri (180 deg)
}

enum class SweepPhase {
    MOVING_STRAIGHT,
    SHIFTING_SIDE
};

enum class TurnDirection {
    TURN_LEFT,
    TURN_RIGHT
};

static SweepPhase currentPhase = SweepPhase::MOVING_STRAIGHT;
static TurnDirection preferredTurn = TurnDirection::TURN_LEFT;
static TurnDirection actualTurn = TurnDirection::TURN_LEFT;
static double shiftTraveled = 0.0;

// JARAK BELOK ZIGZAG DIUBAH MENJADI 0.5 METER
static double shiftTarget = 0.5;

static bool isStrictlyOutOfBounds(double x, double y) {
    return (x > 4.51 || x < -4.51 || y > 3.01 || y < -3.01);
}

static double getAvailableDistance(double x, double y, double heading) {
    double rad = heading * (M_PI / 180.0);
    double step = 0.5;
    double dist = 0.0;
    double currX = x;
    double currY = y;

    while (dist < 3.0) {
        currX += step * std::cos(rad);
        currY += step * std::sin(rad);
        if (isStrictlyOutOfBounds(currX, currY)) {
            break;
        }
        dist += step;
    }
    return dist;
}

// --- SearchState (Pola Zigzag 0.5m) ---
void SearchState::execute(Striker* striker) {
    // Jika melihat bola, langsung menuju ApproachState
    if (striker->hasPerceivedBall()) {
        currentPhase = SweepPhase::MOVING_STRAIGHT;
        preferredTurn = TurnDirection::TURN_LEFT;
        striker->changeState(new ApproachState());
        return;
    }

    double currentHeading = snapTo4Directions(striker->getHeading());
    striker->setHeading(currentHeading);

    if (currentPhase == SweepPhase::MOVING_STRAIGHT) {
        double rad = currentHeading * (M_PI / 180.0);
        double step = 0.5;
        double nextX = striker->getX() + step * std::cos(rad);
        double nextY = striker->getY() + step * std::sin(rad);

        if (!isStrictlyOutOfBounds(nextX, nextY)) {
            striker->setPosition(nextX, nextY);

            double checkFarX = striker->getX() + step * std::cos(rad);
            double checkFarY = striker->getY() + step * std::sin(rad);

            if (isStrictlyOutOfBounds(checkFarX, checkFarY)) {
                double intendedTurnAngle = (preferredTurn == TurnDirection::TURN_LEFT) ? 90.0 : -90.0;
                double intendedHeading = snapTo4Directions(currentHeading + intendedTurnAngle);
                double spaceInIntendedDir = getAvailableDistance(striker->getX(), striker->getY(), intendedHeading);

                if (spaceInIntendedDir >= 0.5) {
                    actualTurn = preferredTurn;
                    striker->setHeading(intendedHeading);
                } else {
                    actualTurn = (preferredTurn == TurnDirection::TURN_LEFT) ? TurnDirection::TURN_RIGHT : TurnDirection::TURN_LEFT;
                    double oppositeTurnAngle = (actualTurn == TurnDirection::TURN_LEFT) ? 90.0 : -90.0;
                    double oppositeHeading = snapTo4Directions(currentHeading + oppositeTurnAngle);
                    striker->setHeading(oppositeHeading);
                }

                currentPhase = SweepPhase::SHIFTING_SIDE;
                shiftTraveled = 0.0;
                shiftTarget = 0.5; // Mengunci jarak belok ke 0.5 meter
            }
        } else {
            double intendedTurnAngle = (preferredTurn == TurnDirection::TURN_LEFT) ? 90.0 : -90.0;
            double intendedHeading = snapTo4Directions(currentHeading + intendedTurnAngle);
            striker->setHeading(intendedHeading);
            currentPhase = SweepPhase::SHIFTING_SIDE;
            shiftTraveled = 0.0;
            shiftTarget = 0.5;
        }
    } 
    else if (currentPhase == SweepPhase::SHIFTING_SIDE) {
        double rad = currentHeading * (M_PI / 180.0);
        double step = 0.5;
        double nextX = striker->getX() + step * std::cos(rad);
        double nextY = striker->getY() + step * std::sin(rad);

        if (!isStrictlyOutOfBounds(nextX, nextY) && shiftTraveled < shiftTarget) {
            striker->setPosition(nextX, nextY);
            shiftTraveled += step;
        }

        double checkNextX = striker->getX() + step * std::cos(rad);
        double checkNextY = striker->getY() + step * std::sin(rad);

        if (isStrictlyOutOfBounds(checkNextX, checkNextY) || shiftTraveled >= shiftTarget) {
            double turnAngle = (actualTurn == TurnDirection::TURN_LEFT) ? 90.0 : -90.0;
            double finalHeading = snapTo4Directions(currentHeading + turnAngle);
            striker->setHeading(finalHeading);

            preferredTurn = (actualTurn == TurnDirection::TURN_LEFT) ? TurnDirection::TURN_RIGHT : TurnDirection::TURN_LEFT;
            currentPhase = SweepPhase::MOVING_STRAIGHT;
        }
    }
}

// --- ApproachState ---
void ApproachState::execute(Striker* striker) {
    if (!striker->hasPerceivedBall()) {
        striker->changeState(new SearchState());
        return;
    }

    auto ballPos = striker->getPerceivedBallPos();

    double targetX = ballPos.x - 0.5;
    double targetY = ballPos.y;

    double distToTarget = Utils::euclideanDistance(striker->getX(), striker->getY(), targetX, targetY);

    if (distToTarget <= 0.2) {
        striker->setPosition(targetX, targetY);
        striker->setHeading(0.0);
        striker->changeState(new AlignState());
        return;
    }

    double moveBearing = Utils::calculateBearing(striker->getX(), striker->getY(), targetX, targetY);
    double moveHeading = snapTo4Directions(moveBearing);
    striker->setHeading(moveHeading);

    double moveRad = moveHeading * (M_PI / 180.0);
    double step = std::min(0.5, distToTarget);

    double nextX = striker->getX() + step * std::cos(moveRad);
    double nextY = striker->getY() + step * std::sin(moveRad);

    striker->setPosition(nextX, nextY);
}

// --- AlignState ---
void AlignState::execute(Striker* striker) {
    striker->setHeading(0.0);
    striker->changeState(new KickState());
}

// --- KickState ---
void KickState::execute(Striker* striker) {
    striker->setNextAction(RobotAction::KICK);
    striker->changeState(new SearchState());
}