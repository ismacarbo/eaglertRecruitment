#ifndef FSM_H
#define FSM_H

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <mutex>

// Enum per rappresentare lo stato
enum Stato {
    Idle,
    Run
};

// Dichiarazione delle funzioni per cambiare e ottenere lo stato
void cambiaStato(Stato nuovoStato);
Stato ottieniStato();
void iniziaLog();
void stopLog();
void processaMessaggio_fsm(const std::string& messaggio);

// Dichiarazione delle variabili globali
extern std::mutex statoMutex;
extern Stato statoCorrente;
extern std::unordered_map<uint16_t, std::vector<long>> messaggi;

#endif // FSM_H
