cmake_minimum_required(VERSION 3.0.0)
project(DataReceiverCLI VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

find_package(asio REQUIRED)
find_package(fmt 7.1.3 REQUIRED)
find_package(spdlog 1.8.0 REQUIRED)
find_package(nlohmann_json 3.9.1 REQUIRED)

add_executable(data-convert data_convert.cpp)
target_link_libraries(data-convert PRIVATE nlohmann_json::nlohmann_json fmt::fmt)

add_executable(data-convert2 data_convert2.cpp)
target_link_libraries(data-convert2 PRIVATE nlohmann_json::nlohmann_json fmt::fmt)