#include <asio.hpp>
#include <chrono>
#include <functional>
#include <vector>
#include <cstdint>
#include <map>
#include <fstream>
#include <algorithm>
#include <spdlog/spdlog.h>
#include <fmt/format.h>
#include <fmt/printf.h>
#include <fmt/ranges.h>
#include <nlohmann/json.hpp>
#include"data_receiver.h"
#include"forza_horizon4_structure.h"

int main()
{
    DataReceiver dataReceiver{ 9999 };
    dataReceiver.run();
}
