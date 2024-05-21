#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <string>

// Dichiarazione delle funzioni
void aggiornaStatistiche(const std::string& id, uint64_t timestamp);
void salvaStatistiche();

struct Statistiche {
    std::vector<uint64_t> timestamps;
};

std::unordered_map<std::string, Statistiche> statisticheMap;

void aggiornaStatistiche(const std::string& id, uint64_t timestamp) {
    auto& stats = statisticheMap[id];
    stats.timestamps.push_back(timestamp);
}

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