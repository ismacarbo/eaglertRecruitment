#include "../fake_receiver.h"
#include "fsm.cpp"
#include "logging.cpp"
#include "statistics.cpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <chrono>

std::mutex queue_mutex;
std::condition_variable queue_cv;
std::queue<std::string> message_queue;
std::atomic<bool> isRunning(false);

void can_receiver_thread() {
    std::string message(MAX_CAN_MESSAGE_SIZE, '\0');

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
                logMessaggio(message);
                uint64_t timestamp = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
                aggiornaStatistiche(message.substr(0, message.find('#')), timestamp);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simula un piccolo ritardo nella ricezione
    }
}

std::thread receiver_thread;

void start_receiver_thread() {
    isRunning = true;
    receiver_thread = std::thread(can_receiver_thread);
}

void stop_receiver_thread() {
    isRunning = false;
    if (receiver_thread.joinable()) {
        receiver_thread.join();
    }
}