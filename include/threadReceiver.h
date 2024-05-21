#ifndef THREAD_RECEIVER_H
#define THREAD_RECEIVER_H

void start_receiver_thread();
void stop_receiver_thread();
int open_can(const char* can_interface);
int can_receive(char* buffer);

#endif // THREAD_RECEIVER_H
#ifndef THREADRECEIVER_H
#define THREADRECEIVER_H

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <string>

// Dichiarazione delle funzioni per gestire il thread di ricezione
void start_receiver_thread();
void stop_receiver_thread();
void can_receiver_thread();

// Dichiarazione delle variabili globali per la coda dei messaggi e la sincronizzazione
extern std::mutex queue_mutex;
extern std::condition_variable queue_cv;
extern std::queue<std::string> message_queue;
extern std::atomic<bool> isRunning;

#endif // THREADRECEIVER_H
