cmake_minimum_required(VERSION 3.10)
project(HFT_Pipeline)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(hft_pipeline
    src/main.cpp
    # src/ZeroMQReceiver.cpp  # Remove if not using ZeroMQ
)

target_link_libraries(hft_pipeline
    ${Boost_LIBRARIES}
    nlohmann_json::nlohmann_json
    CURL::libcurl
    # zmq  # Remove if not using ZeroMQ
)
