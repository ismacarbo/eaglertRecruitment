#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <ctime>
#include <chrono>
#include <cstdint>
#include <sstream>
#include <iomanip>

// Definizione dell'enum per gli stati
enum Stato {
    Idle,
    Run
};

// Dichiarazione delle funzioni e variabili globali
void cambiaStato(Stato nuovoStato);
Stato ottieniStato();
void iniziaLog();
void stopLog();
void processaMessaggio(const std::string& messaggio);

std::mutex statoMutex;
Stato statoCorrente = Idle;
std::ofstream logFile;
std::unordered_map<uint16_t, std::vector<long>> messaggi;

void cambiaStato(Stato nuovoStato) {
    std::lock_guard<std::mutex> lock(statoMutex);
    statoCorrente = nuovoStato;
}

Stato ottieniStato() {
    std::lock_guard<std::mutex> lock(statoMutex);
    return statoCorrente;
}

void iniziaLog() {
    logFile.open("log_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) + ".log");
    messaggi.clear();
}

void stopLog() {
    logFile.close();
}

void processaMessaggio(const std::string& messaggio) {
    uint16_t id;
    std::vector<uint8_t> payload;
    // Simula il parsing del messaggio
    // parseMessaggio(messaggio, id, payload);

    auto ora = std::chrono::system_clock::now().time_since_epoch().count();

    {
        std::lock_guard<std::mutex> lock(statoMutex);
        messaggi[id].push_back(ora);
    }

    if (statoCorrente == Run) {
        if (logFile.is_open()) {
            logFile << ora << " " << messaggio << std::endl;
        }
    }
}