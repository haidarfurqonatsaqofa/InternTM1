#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "Field.hpp"
#include "Ball.hpp"
#include "Striker.hpp"
#include <string>

class Simulator {
private:
    Field field;
    Ball ball;
    Striker striker;
    int currentTick;
    bool running;

public:
    Simulator();

    // Memuat konfigurasi posisi awal robot dan bola dari file teks
    bool loadConfig(const std::string& filename);

    // Menjalankan game loop berbasis tick
    void run();

    // Merender tampilan lapangan ASCII di terminal
    void render() const;
};

#endif // SIMULATOR_HPP