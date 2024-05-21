#include "../include/logging.h"
#include <fstream>

std::ofstream logFile;

void iniziaLog() {
    logFile.open("log.txt", std::ios::out | std::ios::app);
}

void stopLog() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void logMessaggio(const std::string& message) {
    if (logFile.is_open()) {
        logFile << message << std::endl;
    }
}
