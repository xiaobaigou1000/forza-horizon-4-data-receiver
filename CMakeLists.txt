cmake_minimum_required(VERSION 3.0.0)
project(forza-data VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(asio REQUIRED)
find_package(fmt 7.1.3 REQUIRED)
find_package(spdlog 1.8.0 REQUIRED)
find_package(nlohmann_json 3.9.1 REQUIRED)

add_executable(forza-data main.cpp)
target_link_libraries(forza-data fmt::fmt asio::asio)

add_executable(data-convert data_convert.cpp)
target_link_libraries(data-convert PRIVATE nlohmann_json::nlohmann_json fmt::fmt)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
