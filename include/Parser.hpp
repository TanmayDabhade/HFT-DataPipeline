#pragma once
#include "MarketData.hpp"

// Parses a MarketTick from a raw buffer, returns true if successful
bool parseMarketTick(const void* data, size_t size, MarketTick& outTick);
