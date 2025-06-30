#include "Processor.hpp"
#include "LockFreeQueue.hpp"
#include "MarketData.hpp"

#include <iostream>

class VWAPCalculator {
    LockFreeQueue<MarketTick>& inputQueue;
    LockFreeQueue<double>& outputQueue;
public:
    VWAPCalculator(LockFreeQueue<MarketTick>& in, LockFreeQueue<double>& out)
        : inputQueue(in), outputQueue(out) {};
    
    void run() {
        MarketTick tick;
        while (inputQueue.pop(tick)) {
            double vwap = tick.price * tick.size; // Simplified
            outputQueue.push(vwap);
        }
    }
};
