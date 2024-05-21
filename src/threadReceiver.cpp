#include "../include/threadReceiver.h"
#include "../include/fsm.h"
#include "../include/logging.h"
#include "../include/statistics.h"
#include "../fake_receiver.h"
#include <cstring>

// Definizione delle variabili globali per la coda dei messaggi e la sincronizzazione
std::mutex queue_mutex;
std::condition_variable queue_cv;
std::queue<std::string> message_queue;
std::atomic<bool> isRunning(false);
std::thread receiver_thread;

// Funzione che esegue il thread di ricezione dei messaggi CAN
void can_receiver_thread() {
    std::string message(665, '\0');

    while (isRunning) {
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            if (can_receive(&message[0]) > 0) {
                message.resize(strlen(message.c_str())); // Ridimensiona la stringa per contenere solo i dati validi
                if (message == "0A0#6601" || message == "0A0#FF01") {
                    if (ottieniStato() == Idle) {
                        cambiaStato(Run);
                        iniziaLog();
                    }
                } else if (message == "0A0#66FF") {
                    if (ottieniStato() == Run) {
                        cambiaStato(Idle);
                        stopLog();
                        salvaStatistiche();
                    }
                }
                processaMessaggio_logging(message); // Processa e registra il messaggio
                uint64_t timestamp = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
                aggiornaStatistiche(message.substr(0, message.find('#')), timestamp);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simula un piccolo ritardo nella ricezione
    }
}

// Funzione per avviare il thread di ricezione
void start_receiver_thread() {
    isRunning = true;
    receiver_thread = std::thread(can_receiver_thread);
}

// Funzione per fermare il thread di ricezione
void stop_receiver_thread() {
    isRunning = false;
    if (receiver_thread.joinable()) {
        receiver_thread.join();
    }
}
