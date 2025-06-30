#include "Parser.hpp"
#include <cstring>
#include <stdexcept>

// Helper for little-endian systems (assuming you use '<' in struct.pack)
bool parseMarketTick(const void* data, size_t size, MarketTick& outTick) {
    if (size < 24) return false; // Not enough data
    const char* ptr = static_cast<const char*>(data);

    outTick.symbol = std::string(ptr, 4);
    ptr += 4;

    std::memcpy(&outTick.price, ptr, sizeof(double));
    ptr += sizeof(double);

    std::memcpy(&outTick.size, ptr, sizeof(uint32_t));
    ptr += sizeof(uint32_t);

    std::memcpy(&outTick.timestamp, ptr, sizeof(uint64_t));
    return true;
}
