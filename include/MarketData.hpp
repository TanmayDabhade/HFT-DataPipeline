#pragma once
#include <string>
#include <cstdint>

struct MarketTick {
    std::string symbol;
    double price;
    uint32_t size;
    uint64_t timestamp;
};

class MarketDataReceiver {
public:
    virtual ~MarketDataReceiver() = default;
    virtual void start() = 0;
};
