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
#include"telemetry_type.h"
#include"data_receiver.h"
#include"forza_horizon4_structure.h"

int main()
{
    DataReceiver dataReceiver{ 9999 };

    while (true)
    {
        auto result = dataReceiver.getData();
        if (result.convertCurrentEngineRpm() < 100.0f)
        {
            continue;
        }
        spdlog::info("Engine RPM: {}, Power: {}, Speed: {}", result.convertCurrentEngineRpm(), result.convertPower(), result.convertSpeed());
    }
}
