#include "../include/logging.h"
#include <iostream>
#include <ctime>

// Funzione per iniziare il logging
void iniziaLogLogging() {
    std::string fileName = "../candump.log";
    logFile.open(fileName, std::ios::out);
    if (logFile.is_open()) {
        std::cout << "Logging started: " << fileName << std::endl;
    }
}

// Funzione per fermare il logging
void fineLog() {
    if (logFile.is_open()) {
        logFile.close();
        std::cout << "Logging stopped." << std::endl;
    }
}

// Funzione per processare e registrare un messaggio nel log
void processaMessaggio_logging(const std::string& message) {
    if (logFile.is_open()) {
        logFile << std::time(nullptr) << " " << message << std::endl;
    }
}
