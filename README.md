# HFT-DataPipeline

## Overview

The **HFT-DataPipeline** is a high-performance, modular C++ system for simulating and processing financial market data in real time, closely mimicking how data pipelines in High-Frequency Trading (HFT) systems operate. It supports ingestion of raw ITCH market data, parsing it into structured events, and distributing it using ZeroMQ for downstream consumption or further analysis.

## Features

- 🔁 **ZeroMQ Feed Receiver**: Efficient asynchronous data ingestion from a mock market data feed.
- 📦 **ITCH Parser**: Parses binary ITCH files into structured market data events.
- ⚙️ **Processor**: Processes parsed data for analytics or storage.
- 🚀 **Lock-Free Queues**: Ensures minimal latency and high throughput.
- 🧪 **Mock Feed Generator**: Simulates real-time exchange feeds using Python for testing.
- 🏗️ **CMake Build System**: Clean and configurable build process.

## Directory Structure

```

├── CMakeLists.txt               # Build configuration
├── include/                     # Header files (core logic)
├── src/                         # Source files for implementation
├── data/                        # Sample binary ITCH data
├── scripts/                     # Feed simulation script
├── build/                       # Generated build files
├── README.md                    # Project documentation

````

## Dependencies

- C++17 or above
- ZeroMQ
- CMake (>= 3.10)
- Python 3 (for mock feed)

## Setup Instructions

### 1. Build the project

```bash
mkdir build
cd build
cmake ..
make
````

### 2. Run the mock feed

```bash
python3 scripts/mock_feed.py
```

### 3. Start the pipeline

```bash
./build/hft_pipeline
```

## Use Case

This project can be used for:

* Simulating high-frequency trading environments
* Learning about lock-free data structures and real-time data ingestion
* Benchmarking or designing real-world trading system components

## Contributing

Contributions are welcome! Please submit a pull request or raise issues for bugs, improvements, or ideas.

## License

MIT License

```
