#include "../include/threadReceiver.h"
#include "../include/fsm.h"
#include "../include/logging.h"
#include "../include/statistics.h"
#include "../fake_receiver.h"
#include <cstring>

// Definizione delle variabili globali per la coda dei messaggi e la sincronizzazione
std::mutex codaMutex;
std::condition_variable codaCV;
std::queue<std::string> codaMessaggi;
std::atomic<bool> inEsecuzione(false);
std::thread threadRicezione;

// Funzione che esegue il thread di ricezione dei messaggi CAN
void threadRicezioneCAN() {
    std::string messaggio(665, '\0');

    while (inEsecuzione) {
        {
            std::lock_guard<std::mutex> lock(codaMutex);
            if (can_receive(&messaggio[0]) > 0) {
                messaggio.resize(strlen(messaggio.c_str())); // Ridimensiona la stringa per contenere solo i dati validi
                if (messaggio == "0A0#6601" || messaggio == "0A0#FF01") {
                    if (ottieniStato() == Inattivo) {
                        cambiaStato(Esecuzione);
                        iniziaLog();
                    }
                } else if (messaggio == "0A0#66FF") {
                    if (ottieniStato() == Esecuzione) {
                        cambiaStato(Inattivo);
                        fermaLog();
                        salvaStatistiche();
                    }
                }
                processaMessaggio_logging(messaggio); // Processa e registra il messaggio
                uint64_t timestamp = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
                aggiornaStatistiche(messaggio.substr(0, messaggio.find('#')), timestamp);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simula un piccolo ritardo nella ricezione
    }
}

// Funzione per avviare il thread di ricezione
void avviaThreadRicezione() {
    inEsecuzione = true;
    threadRicezione = std::thread(threadRicezioneCAN);
}

// Funzione per fermare il thread di ricezione
void fermaThreadRicezione() {
    inEsecuzione = false;
    if (threadRicezione.joinable()) {
        threadRicezione.join();
    }
}
