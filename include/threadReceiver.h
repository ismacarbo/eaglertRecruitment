#ifndef THREAD_RECEIVER_H
#define THREAD_RECEIVER_H

void start_receiver_thread();
void stop_receiver_thread();
int open_can(const char* can_interface);
int can_receive(char* buffer);

#endif // THREAD_RECEIVER_H
