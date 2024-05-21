#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <fstream>

// Dichiarazione delle funzioni per il logging
void iniziaLogLogging();
void fineLog();
void processaMessaggio_logging(const std::string& message);

// Dichiarazione del file di log
extern std::ofstream logFile;

#endif // LOGGING_H
