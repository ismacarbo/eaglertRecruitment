#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <stdio.h>
#include <iostream>

extern std::ofstream fileLog;

//inserisce i messaggi nel file di log
void log_messaggio(const std::string& messaggio) {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    fileLog << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << " " << messaggio << std::endl;
}
