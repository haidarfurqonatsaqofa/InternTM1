#include "../include/Simulator.hpp"
#include <iostream>

int main() {
    Simulator sim;

    // Coba muat konfigurasi dari file (Level 3 Extra Feature)
    if (!sim.loadConfig("config.txt")) {
        std::cout << "[INFO] File config.txt tidak ditemukan. Menggunakan posisi default.\n";
    }

    sim.run();
    return 0;
}