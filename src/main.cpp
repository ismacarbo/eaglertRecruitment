#include "../include/fsm.h"
#include "../include/logging.h"
#include "../include/statistics.h"
#include "../include/threadReceiver.h"
#include "../fake_receiver.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

// Funzione di esempio per processare un messaggio
void processaMessaggio2(const std::string &messaggio) {
    std::cout << "Messaggio In Ricezione: " << messaggio << std::endl;
}

int main() {
    // Apertura del file CAN simulato
    if (open_can("candump.log") != 0) {
        std::cerr << "Errore nell'apertura del file CAN simulato" << std::endl;
        return -1;
    }

    // Avvio del thread di ricezione
    avviaThreadRicezione();

    // Loop principale per processare i messaggi dalla coda
    while (true) {
        std::unique_lock<std::mutex> lock(codaMutex);
        codaCV.wait(lock, [] { return !codaMessaggi.empty(); });

        while (!codaMessaggi.empty()) {
            std::string msg = codaMessaggi.front();
            codaMessaggi.pop();
            lock.unlock();
            processaMessaggio2(msg);
            lock.lock();
        }
    }

    // Ferma il thread di ricezione
    fermaThreadRicezione();

    // Chiude il file CAN simulato
    close_can();

    return 0;
}
