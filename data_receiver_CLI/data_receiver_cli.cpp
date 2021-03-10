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

int main()
{
    auto telemetryTypes = TelemetryType::parse_config("config.json");

    DataReceiver dataReceiver{ 9999 };
    dataReceiver.updateTelemetryTypeInfo(telemetryTypes);

    std::vector<TelemetryType> dataConcerned;
    dataConcerned.push_back(*std::find(telemetryTypes.begin(), telemetryTypes.end(), "CurrentEngineRpm"));
    dataConcerned.push_back(*std::find(telemetryTypes.begin(), telemetryTypes.end(), "Speed"));
    dataConcerned.push_back(*std::find(telemetryTypes.begin(), telemetryTypes.end(), "Power"));

    while (true)
    {
        spdlog::info("{}",dataReceiver.receiveAndProcessDataCLI(dataConcerned));
    }
}
