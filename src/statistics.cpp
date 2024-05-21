#include "../include/statistics.h"
#include <fstream>

// Definizione della mappa delle statistiche
std::unordered_map<std::string, Statistiche> mappaStatistiche;

// Funzione per aggiornare le statistiche con un nuovo timestamp
void aggiornaStatistiche(const std::string& id, uint64_t timestamp) {
    auto& stats = mappaStatistiche[id];
    stats.timestamp.push_back(timestamp);
}

// Funzione per salvare le statistiche in un file CSV
void salvaStatistiche() {
    std::ofstream fileStatistiche("statistiche.csv", std::ios::out);
    if (fileStatistiche.is_open()) {
        fileStatistiche << "ID,Numero di Messaggi,Tempo Medio (ms)\n";
        for (const auto& pair : mappaStatistiche) {
            const auto& id = pair.first;
            const auto& stats = pair.second;
            if (stats.timestamp.size() > 1) {
                uint64_t tempoTotale = 0;
                for (size_t i = 1; i < stats.timestamp.size(); ++i) {
                    tempoTotale += (stats.timestamp[i] - stats.timestamp[i - 1]);
                }
                uint64_t tempoMedio = tempoTotale / (stats.timestamp.size() - 1);
                fileStatistiche << id << "," << stats.timestamp.size() << "," << tempoMedio << "\n";
            } else {
                fileStatistiche << id << "," << stats.timestamp.size() << ",N/A\n";
            }
        }
        fileStatistiche.close();
    }
}
