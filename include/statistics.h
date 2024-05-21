#ifndef STATISTICS_H
#define STATISTICS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

struct Statistiche {
    std::vector<uint64_t> timestamps;
};

void aggiornaStatistiche(const std::string& id, uint64_t timestamp);
void salvaStatistiche();

extern std::unordered_map<std::string, Statistiche> statistiche;

#endif // STATISTICS_H
