#include "../fake_receiver.h"
#include "fsm.cpp"
#include "logging.cpp"
#include "statistics.cpp"
#include "threadReceiver.cpp"

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

// Variabili globali e sincronizzazione
extern std::mutex queue_mutex;
extern std::condition_variable queue_cv;
extern std::queue<std::string> message_queue;
extern std::atomic<bool> isRunning;

void processaMessaggio(const std::string &message) {
    std::cout << "Processing message: " << message << std::endl;
}

int main() {
    // Apertura del file CAN simulato
    if (open_can("path_to_fake_can_data.txt") != 0) {
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
            processaMessaggio(msg);
            lock.lock();
        }

        // Aggiungere logica per terminare il loop, per esempio una condizione di uscita
        // if (some_condition_to_exit) {
        //     break;
        // }
    }

    // Ferma il thread di ricezione
    stop_receiver_thread();