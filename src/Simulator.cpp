#include "Simulator.hpp"
#include <iostream>
#include <thread>
#include <chrono>

Simulator::Simulator() 
    : currentTick(0), running(true), striker(0.0, 0.0, 0.0), ball(0.0, 0.0) {}

Simulator::Simulator(double startX, double startY, double startHeading, double ballX, double ballY)
    : currentTick(0), running(true), striker(startX, startY, startHeading), ball(ballX, ballY) {}

void Simulator::run() {
    while (running) {
        currentTick++;

        // 1. SENSE: Robot memindai lingkungan & bola
        striker.sense(ball);

        // 2. THINK: Robot menentukan state (Search/Approach/Align/Kick)
        striker.think();

        // 3. ACT: Robot mengeksekusi gerakan atau perintah tendang
        try {
            striker.act(field, ball);
        } catch (const std::exception& e) {
            std::cout << "[ERROR] " << e.what() << "\n";
        }

        // 4. UPDATE PHYSICS: Kecepatan & posisi bola diperbarui
        ball.update();

        // 5. RENDER: Tampilkan grid di terminal
        render();

        // Cek kondisi Gol
        if (field.isGoal(ball.getX(), ball.getY())) {
            std::cout << "\n=== GOAL!!! Striker berhasil mencetak gol! ===\n";
            running = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Simulator::render() const