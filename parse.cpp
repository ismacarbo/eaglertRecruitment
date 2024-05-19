#include <string>
#include <vector>
#include <cstdint>
#include <sstream>

// Funzione per parsare i messaggi ricevuti
void parseMessaggio(const std::string& messaggio, uint16_t& id, std::vector<uint8_t>& payload) {
    std::stringstream ss(messaggio);
    std::string id_str, payload_str;

    if (std::getline(ss, id_str, '#') && std::getline(ss, payload_str)) {
        id = static_cast<uint16_t>(std::stoul(id_str, nullptr, 16));
        payload.clear();
        for (size_t i = 0; i < payload_str.size(); i += 2) {
            payload.push_back(static_cast<uint8_t>(std::stoul(payload_str.substr(i, 2), nullptr, 16)));
        }
    }
}
