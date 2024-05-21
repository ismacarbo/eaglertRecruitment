#include <string>
#include <vector>
#include <cstdint>
#include <sstream>
#include "../include/fsm.h"
#include "../include/logging.h"
#include "../include/statistics.h"
#include "../include/threadReceiver.h"
#include "../include/parse.h"

// Funzione per parsare i messaggi ricevuti
void parseMessaggio(const std::string& messaggio, uint16_t& id, std::vector<uint8_t>& payload) {
    std::stringstream ss(messaggio);
    std::string id_str, payload_str;

    //divido per # il codice ricevuto
    if (std::getline(ss, id_str, '#') && std::getline(ss, payload_str)) {
        //converto l'ID da stringa esadecimale a uint16_t
        id = static_cast<uint16_t>(std::stoul(id_str, nullptr, 16));
        payload.clear(); //pulisco il payload
        
        //converto il payload da stringa esadecimale a un vettore di uint8_t
        //ogni due caratteri (byte HEX)
        for (size_t i = 0; i < payload_str.size(); i += 2) {
            payload.push_back(static_cast<uint8_t>(std::stoul(payload_str.substr(i, 2), nullptr, 16)));
        }
    }
}
