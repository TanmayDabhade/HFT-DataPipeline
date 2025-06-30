#pragma once
#include <boost/lockfree/spsc_queue.hpp>
#include <cstddef>

template<typename T>
class LockFreeQueue {
private:
    boost::lockfree::spsc_queue<T> queue;
public:
    LockFreeQueue(size_t size) : queue(size) {}
    bool push(const T& item) { return queue.push(item); }
    bool pop(T& item) { return queue.pop(item); }
};
