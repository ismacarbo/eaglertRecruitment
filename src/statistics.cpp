#include "../include/statistics.h"
#include <fstream>

// Definizione della mappa delle statistiche
std::unordered_map<std::string, Statistiche> statisticheMap;

// Funzione per aggiornare le statistiche con un nuovo timestamp
void aggiornaStatistiche(const std::string& id, uint64_t timestamp) {
    auto& stats = statisticheMap[id];
    stats.timestamps.push_back(timestamp);
}

// Funzione per salvare le statistiche in un file CSV
void salvaStatistiche() {
    std::ofstream statsFile("statistics.csv", std::ios::out);
    if (statsFile.is_open()) {
        statsFile << "ID,Numero di Messaggi,Tempo Medio (ms)\n";
        for (const auto& pair : statisticheMap) {
            const auto& id = pair.first;
            const auto& stats = pair.second;
            if (stats.timestamps.size() > 1) {
                uint64_t total_time = 0;
                for (size_t i = 1; i < stats.timestamps.size(); ++i) {
                    total_time += (stats.timestamps[i] - stats.timestamps[i - 1]);
                }
                uint64_t mean_time = total_time / (stats.timestamps.size() - 1);
                statsFile << id << "," << stats.timestamps.size() << "," << mean_time << "\n";
            } else {
                statsFile << id << "," << stats.timestamps.size() << ",N/A\n";
            }
        }
        statsFile.close();
    }
}
