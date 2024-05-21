#ifndef STATISTICS_H
#define STATISTICS_H

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>

// Struttura per mantenere le statistiche
struct Statistiche {
    std::vector<uint64_t> timestamps;
};

// Dichiarazione delle funzioni per aggiornare e salvare le statistiche
void aggiornaStatistiche(const std::string& id, uint64_t timestamp);
void salvaStatistiche();

// Dichiarazione della mappa delle statistiche
extern std::unordered_map<std::string, Statistiche> statisticheMap;

#endif // STATISTICS_H
    