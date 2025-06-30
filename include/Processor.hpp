#pragma once
#include "LockFreeQueue.hpp"
#include "MarketData.hpp"

class VWAPCalculator {
    LockFreeQueue<MarketTick>& input_queue_;
    LockFreeQueue<double>& output_queue_;
    double total_price_volume_ = 0.0;
    uint64_t total_volume_ = 0;
public:
    VWAPCalculator(LockFreeQueue<MarketTick>& in, LockFreeQueue<double>& out)
        : input_queue_(in), output_queue_(out) {}

    void run() {
        MarketTick tick;
        while (true) {
            if (input_queue_.pop(tick)) {
                update_vwap(tick);
                output_queue_.push(current_vwap());
            }
        }
    }
private:
    void update_vwap(const MarketTick& tick) {
        total_price_volume_ += tick.price * tick.size;
        total_volume_ += tick.size;
    }
    double current_vwap() const {
        return (total_volume_ == 0) ? 0.0 : total_price_volume_ / total_volume_;
    }
};
