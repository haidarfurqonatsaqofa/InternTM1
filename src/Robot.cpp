#include "Robot.hpp"
#include <iostream>

void Robot::act(Field& field, Ball& ball) {
    (void)field;

    if (nextAction == RobotAction::KICK) {
        // Tendang bola searah heading robot saat ini (misal 0 derajat ke gawang Kanan)
        ball.kick(heading);
        
        // Riset persepsi bola agar robot dapat mencari bola kembali secara bersih
        perceivedBallPos = std::nullopt;
        nextAction = RobotAction::NONE;

        std::cout << "\n[ACTION] BOOM! Robot MENENDANG BOLA ke arah gawang (" << heading << " derajat)!\n";
    }
}