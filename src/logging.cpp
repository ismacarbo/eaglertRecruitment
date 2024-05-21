#include "../include/logging.h"
#include <iostream>
#include <ctime>

// Funzione per iniziare il logging
void iniziaLogLogging() {
    std::string nomeFile = "../candump.log";
    fileLog.open(nomeFile, std::ios::out);
    if (fileLog.is_open()) {
        std::cout << "Registrazione avviata: " << nomeFile << std::endl;
    }
}

// Funzione per fermare il logging
void stopLog() {
    if (fileLog.is_open()) {
        fileLog.close();
        std::cout << "Registrazione fermata." << std::endl;
    }
}

// Funzione per processare e registrare un messaggio nel log
void processaMessaggio_logging(const std::string& messaggio) {
    if (fileLog.is_open()) {
        fileLog << std::time(nullptr) << " " << messaggio << std::endl;
    }
}
