#include "ZeroMQReceiver.hpp"
#include <cstring>
#include <iostream>
#include "Parser.hpp"


ZeroMQReceiver::ZeroMQReceiver(LockFreeQueue<MarketTick>& queue)
    : ctx_(1), socket_(ctx_, ZMQ_SUB), queue_(queue) {
    socket_.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket_.connect("tcp://127.0.0.1:5555");
}

void ZeroMQReceiver::start() {
    while (true) {
        zmq::message_t msg;
        if (!socket_.recv(msg, zmq::recv_flags::none)) continue;
        try {
            MarketTick tick = parseFromBinary(msg.data(), msg.size());
            queue_.push(tick);
        } catch (const std::exception& e) {
            std::cerr << "Parse error: " << e.what() << "\n";
        }
    }
}

MarketTick ZeroMQReceiver::parseFromBinary(void* data, size_t size) {
    if (size < 24) throw std::runtime_error("Invalid message size");
    MarketTick tick;
    char* ptr = static_cast<char*>(data);
    tick.symbol = std::string(ptr, 4);
    ptr += 4;
    std::memcpy(&tick.price, ptr, sizeof(double));
    ptr += sizeof(double);
    std::memcpy(&tick.size, ptr, sizeof(uint32_t));
    ptr += sizeof(uint32_t);
    std::memcpy(&tick.timestamp, ptr, sizeof(uint64_t));
    return tick;
}


