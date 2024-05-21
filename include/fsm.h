#ifndef FSM_H
#define FSM_H

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <mutex>

// Enum per rappresentare gli stati del sistema
enum Stato {
    Inattivo,  // Sistema inattivo
    Esecuzione // Sistema in esecuzione
};

// Dichiarazione delle funzioni per gestire gli stati e i log
void cambiaStato(Stato nuovoStato);
Stato ottieniStato();
void iniziaLog();
void fermaLog();
void processaMessaggio_fsm(const std::string& messaggio);

// Dichiarazione delle variabili globali
extern std::mutex statoMutex;
extern Stato statoCorrente;
extern std::unordered_map<uint16_t, std::vector<long>> messaggi;

#endif // FSM_H
