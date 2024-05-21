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
void processaMessaggio2(const std::string &message) {
    std::cout << "Processing message: " << message << std::endl;
}

int main() {
    // Apertura del file CAN simulato
    if (open_can("../candump.log") != 0) {
        std::cerr << "Errore nell'apertura del file CAN simulato" << std::endl;
        return -1;
    }

    // Avvio del thread di ricezione
    start_receiver_thread();

    // Loop principale per processare i messaggi dalla coda
    while (true) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        queue_cv.wait(lock, [] { return !message_queue.empty(); });

        while (!message_queue.empty()) {
            std::string msg = message_queue.front();
            message_queue.pop();
            lock.unlock();
            processaMessaggio2(msg);
            lock.lock();
        }

        // Aggiungere logica per terminare il loop, per esempio una condizione di uscita
        // if (some_condition_to_exit) {
        //     break;
        // }
    }

    // Ferma il thread di ricezione
    stop_receiver_thread();

    // Chiude il file CAN simulato
    close_can();

    return 0;
}
