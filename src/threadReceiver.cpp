#include "fake_receiver.h"
#include "fsm.cpp"
#include <thread>
#include <mutex>

std::mutex mutexCAN;
std::thread receiver_thread;
bool isRunning = true;

//riceve i messaggi dal CAN
void threadRicevitoreCAN() {
    std::string message(MAX_CAN_MESSAGE_SIZE, '\0');

    while (isRunning) {
        {
            std::lock_guard<std::mutex> lock(mutexCAN);
            if (can_receive(&message[0]) > 0) {
                if (message == "0A0#6601" || message == "0A0#FF01") {
                    std::lock_guard<std::mutex> statoLock(statoMutex);
                    if (statoCorrente == Idle) {
                        statoCorrente = Run;
                        iniziaLog();
                    }
                } else if (message == "0A0#66FF") {
                    std::lock_guard<std::mutex> statoLock(statoMutex);
                    if (statoCorrente == Run) {
                        statoCorrente = Idle;
                        stopLog();
                    }
                }
                processaMessaggio(message);
            }
        }
    }
}

//stoppa il thread che riceve i messaggi dal CAN
void fermaThreadRicezione() {
    isRunning = false;
    if (receiver_thread.joinable()) {
        receiver_thread.join();
    }
}

//avvia il thread che riceve i messaggi dal CAN
void iniziaThreadRicezione() {
    isRunning = true;
    receiver_thread = std::thread(threadRicevitoreCAN);
}
