#include "MarketData.hpp"
#include "ZeroMQReceiver.hpp"
#include "Processor.hpp"
#include "LockFreeQueue.hpp"
#include <thread>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>


size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

nlohmann::json fetch_intraday(const std::string& symbol, const std::string& api_key) {
    CURL* curl;
    std::string readBuffer;
    std::string url = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=" + symbol + "&apikey=" + api_key;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return nlohmann::json::parse(readBuffer);
}

void fetch_and_feed(const std::string& symbol, const std::string& api_key, LockFreeQueue<MarketTick>& rawQueue) {
    while (true) {
        auto json = fetch_intraday(symbol, api_key);
        if (json.contains("Global Quote")) {
            MarketTick tick;
            tick.symbol = json["Global Quote"]["01. symbol"];
            tick.price = std::stod(json["Global Quote"]["05. price"].get<std::string>());
            tick.size = std::stoul(json["Global Quote"]["06. volume"].get<std::string>());
            tick.timestamp = std::time(nullptr);
            rawQueue.push(tick);
        }
        std::this_thread::sleep_for(std::chrono::seconds(12));
    }
}


int main() {
    LockFreeQueue<MarketTick> rawQueue(1024);
    LockFreeQueue<double> processedQueue(1024);

    std::string api_key = "IQAHIUQQR532GBQ8";
    std::string symbol = "AAPL";
    std::thread fetchThread(fetch_and_feed, symbol, api_key, std::ref(rawQueue));

    VWAPCalculator calculator(rawQueue, processedQueue);
    std::thread processThread([&]() { calculator.run(); });

    std::thread storageThread([&]() {
        double result;
        while (true) {
            if (processedQueue.pop(result)) {
                std::cout << "Processed VWAP: " << result << "\n";
            }
        }
    });

    fetchThread.join();
    processThread.join();
    storageThread.join();
    return 0;
}



// // In your main():
// std::thread fetchThread(fetch_and_feed, "AAPL", api_key, std::ref(rawQueue));





// int main() {
//     LockFreeQueue<MarketTick> rawQueue(1024);
//     LockFreeQueue<double> processedQueue(1024);

//     ZeroMQReceiver receiver(rawQueue);
//     std::thread ingestThread([&]() { receiver.start(); });

//     VWAPCalculator calculator(rawQueue, processedQueue);
//     std::thread processThread([&]() { calculator.run(); });

//     std::thread storageThread([&]() {
//         double result;
//         while (true) {
//             if (processedQueue.pop(result)) {
//                 std::cout << "Processed VWAP: " << result << "\n";
//             }
//         }
//     });

//     ingestThread.join();
//     processThread.join();
//     storageThread.join();
//     return 0;
// }
