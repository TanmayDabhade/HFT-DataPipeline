#pragma once
#include "MarketData.hpp"
#include "LockFreeQueue.hpp"
#include <zmq.hpp>
#include <string>

class ZeroMQReceiver : public MarketDataReceiver {
    zmq::context_t ctx_;
    zmq::socket_t socket_;
    LockFreeQueue<MarketTick>& queue_;
public:
    ZeroMQReceiver(LockFreeQueue<MarketTick>& queue);
    void start() override;
private:
    MarketTick parseFromBinary(void* data, size_t size);
};
