#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

// Dichiarazione delle funzioni
void iniziaLog();
void stopLog();
void logMessaggio(const std::string& message);

std::ofstream logFile;

void iniziaLog() {
    std::string fileName = "log_" + std::to_string(std::time(nullptr)) + ".txt";
    logFile.open(fileName, std::ios::out);
    if (logFile.is_open()) {
        std::cout << "Logging started: " << fileName << std::endl;
    }
}

void stopLog() {
    if (logFile.is_open()) {
        logFile.close();
        std::cout << "Logging stopped." << std::endl;
    }
}

void logMessaggio(const std::string& message) {
    if (logFile.is_open()) {
        logFile << std::time(nullptr) << " " << message << std::endl;
    }
}
