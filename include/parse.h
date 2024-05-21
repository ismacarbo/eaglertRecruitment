#ifndef PARSE_H
#define PARSE_H

#include <string>
#include <vector>
#include <cstdint>

void parseMessaggio(const std::string& message, uint16_t& id, std::vector<uint8_t>& payload);

#endif // PARSE_H
