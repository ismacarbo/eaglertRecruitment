#ifndef THREADRECEIVER_H
#define THREADRECEIVER_H

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <string>

// Dichiarazione delle funzioni per gestire il thread di ricezione
void avviaThreadRicezione();
void fermaThreadRicezione();
void threadRicezioneCAN();

// Dichiarazione delle variabili globali per la coda dei messaggi e la sincronizzazione
extern std::mutex codaMutex;
extern std::condition_variable codaCV;
extern std::queue<std::string> codaMessaggi;
extern std::atomic<bool> inEsecuzione;

#endif // THREADRECEIVER_H
