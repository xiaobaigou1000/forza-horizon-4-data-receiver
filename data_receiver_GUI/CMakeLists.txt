cmake_minimum_required(VERSION 3.0.0)
project(DataReceiverGUI VERSION 0.1.0)

find_package(asio REQUIRED)
find_package(fmt 7.1.3 REQUIRED)
find_package(spdlog 1.8.0 REQUIRED)
find_package(nlohmann_json 3.9.1 REQUIRED)

include(FetchContent) 
FetchContent_Declare(mahi-gui GIT_REPOSITORY https://github.com/mahilab/mahi-gui.git) 
FetchContent_MakeAvailable(mahi-gui)

add_executable(DataReceiverGUI "data_receiver_gui.cpp" "include/data_receiver.h" "include/plot_function_utilities.h")
target_include_directories(DataReceiverGUI PRIVATE include)
target_link_libraries(DataReceiverGUI PRIVATE mahi::gui fmt::fmt)