cmake_minimum_required(VERSION 3.0.0)
project(forza-data VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

add_subdirectory(data_receiver_CLI)
add_subdirectory(data_process)
add_subdirectory(data_receiver_GUI)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
