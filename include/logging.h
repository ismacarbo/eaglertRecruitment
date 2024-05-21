#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <fstream>

// Dichiarazione delle funzioni per il logging
void iniziaLogLogging();
void stopLog();
void processaMessaggio_logging(const std::string& messaggio);

// Dichiarazione del file di log
extern std::ofstream fileLog;

#endif // LOGGING_H
