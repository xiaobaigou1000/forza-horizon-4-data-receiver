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

enum class DataType
{
    s32,
    u32,
    f32,
    u16,
    u8,
    s8,
    hzn
};

const std::map<std::string, std::tuple<DataType, size_t>> dataTypeQuery{
    {"s32", {DataType::s32, 4}},
    {"u32", {DataType::u32, 4}},
    {"f32", {DataType::f32, 4}},
    {"u16", {DataType::u16, 2}},
    {"u8", {DataType::u8, 1}},
    {"s8", {DataType::s8, 1}},
    {"hzn", {DataType::hzn, 12}} };

class TelemetryType
{
public:
    std::string name;
    DataType type;
    size_t size;
    size_t position;

    TelemetryType(std::string_view name, DataType type = DataType::hzn, size_t size = 0, size_t position = 0)
        : name(name), type(type), size(size), position(position) {}

    bool operator==(const TelemetryType& rhd)
    {
        return name == rhd.name;
    }

    bool operator==(std::string_view rhdName)
    {
        return name == rhdName;
    }
};

std::vector<TelemetryType> read_config(std::string_view fileName)
{
    std::ifstream configFile(fileName.data());
    std::vector<char> buffer;
    std::copy(std::istreambuf_iterator<char>(configFile), std::istreambuf_iterator<char>(), std::back_inserter(buffer));
    nlohmann::json config_json = nlohmann::json::parse(buffer);

    std::vector<TelemetryType> telemetryTypes;
    size_t position = 0;
    for (const auto& i : config_json)
    {
        const std::string typeStr = i["type"];

        auto typeInfo = std::get<1>(*dataTypeQuery.find(typeStr));
        DataType dataType = std::get<0>(typeInfo);
        size_t size = std::get<1>(typeInfo);

        telemetryTypes.push_back({ i["name"], dataType, size, position });
        position += size;
    }

    return telemetryTypes;
}

int main()
{
    using asio::ip::udp;
    using namespace std::chrono_literals;

    auto telemetryTypes = read_config("forza-horizon-4-data-format.json");

    std::ofstream logger("log.txt");
    std::for_each(telemetryTypes.begin(), telemetryTypes.end(), [&logger](auto i) {logger << i.name << ",";});
    logger << "\n";

    asio::io_context io;

    auto receiveForzaPackages = [&io, &telemetryTypes, &logger] {
        const auto currentEngineRPMTypeInfo = *std::find(telemetryTypes.begin(), telemetryTypes.end(), "CurrentEngineRpm");
        const auto currentSpeedTypeInfo = *std::find(telemetryTypes.begin(), telemetryTypes.end(), "Speed");//multiply 2.237
        const auto currentPowerTypeInfo = *std::find(telemetryTypes.begin(), telemetryTypes.end(), "Power");//devide 745.7

        udp::socket socket(io, udp::endpoint(udp::v4(), 9999));
        std::vector<uint8_t> receive_buffer(1024);
        while (true)
        {
            udp::endpoint remote_endpoint;
            size_t len = socket.receive_from(asio::buffer(receive_buffer), remote_endpoint);

            uint8_t* dataPointer = receive_buffer.data();

            uint8_t engineRPM[4];
            uint8_t speed[4];
            uint8_t power[4];
            std::copy(dataPointer + currentEngineRPMTypeInfo.position, dataPointer + currentEngineRPMTypeInfo.position + currentEngineRPMTypeInfo.size, engineRPM);
            std::copy(dataPointer + currentSpeedTypeInfo.position, dataPointer + currentSpeedTypeInfo.position + currentSpeedTypeInfo.size, speed);
            std::copy(dataPointer + currentPowerTypeInfo.position, dataPointer + currentPowerTypeInfo.position + currentPowerTypeInfo.size, power);

            for (const auto& i : telemetryTypes)
            {
                std::string value;
                uint8_t data[12];
                std::copy(i.position + dataPointer, i.position + dataPointer + i.size, data);

                switch (i.type)
                {
                case DataType::s32:
                    value = fmt::format("{}", *reinterpret_cast<int32_t*>(data));
                    break;
                case DataType::u32:
                    value = fmt::format("{}", *reinterpret_cast<uint32_t*>(data));
                    break;
                case DataType::f32:
                    value = fmt::format("{}", *reinterpret_cast<float*>(data));
                    break;
                case DataType::s8:
                    value = fmt::format("{}", *reinterpret_cast<int8_t*>(data));
                    break;
                case DataType::u16:
                    value = fmt::format("{}", *reinterpret_cast<uint16_t*>(data));
                    break;
                case DataType::u8:
                    value = fmt::format("{}", *reinterpret_cast<uint8_t*>(data));
                    break;
                }

                if (i.name == "Speed")
                {
                    spdlog::info("DataName: {}, DataType: {}, Position: {}, Value: {}", i.name, i.type, i.position, *reinterpret_cast<float*>(data) * 2.237);
                }
                logger << value << ",";
            }
            logger << "\n";
            // spdlog::info("Package size: {} Current Engine RPM: {: 6.0f}, Current Speed: {: 10.4f}, Current Power: {: 10.4f}", len, *reinterpret_cast<float*>(engineRPM), *reinterpret_cast<float*>(speed), *reinterpret_cast<float*>(power));
        }
    };

    io.dispatch(receiveForzaPackages);
    io.run();
}
