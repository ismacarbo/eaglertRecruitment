#include "../include/fsm.h"
#include <chrono>

// Definizione delle variabili globali
std::mutex statoMutex;
Stato statoCorrente = Idle;
std::unordered_map<uint16_t, std::vector<long>> messaggi;
std::ofstream logFile; // Definizione del file di log

// Funzione per cambiare lo stato
void cambiaStato(Stato nuovoStato) {
    std::lock_guard<std::mutex> lock(statoMutex);
    statoCorrente = nuovoStato;
}

// Funzione per ottenere lo stato corrente
Stato ottieniStato() {
    std::lock_guard<std::mutex> lock(statoMutex);
    return statoCorrente;
}

// Funzione per iniziare il log
void iniziaLog() {
    logFile.open("log_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) + ".log");
    messaggi.clear();
}

// Funzione per fermare il log
void stopLog() {
    logFile.close();
}

// Funzione per processare un messaggio nello stato FSM
void processaMessaggio_fsm(const std::string& messaggio) {
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
    