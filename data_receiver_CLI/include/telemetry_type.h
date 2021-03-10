#pragma once
#include<string_view>
#include<spdlog/spdlog.h>

class TelemetryType
{
public:
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

    std::string name;
    DataType type;
    size_t size;
    size_t position;
    float scaler;

    TelemetryType(std::string_view name, DataType type = DataType::hzn, size_t size = 0, size_t position = 0, float scaler = 1.0f)
        : name(name), type(type), size(size), position(position), scaler(scaler) {}

    bool operator==(const TelemetryType& rhd)
    {
        return name == rhd.name;
    }

    bool operator==(std::string_view rhdName)
    {
        return name == rhdName;
    }

    static std::vector<TelemetryType> parse_config(std::string_view fileName)
    {
        using DataType = TelemetryType::DataType;

        const std::map<std::string, std::tuple<DataType, size_t>> dataTypeQuery{
            {"s32", {DataType::s32, 4}},
            {"u32", {DataType::u32, 4}},
            {"f32", {DataType::f32, 4}},
            {"u16", {DataType::u16, 2}},
            {"u8", {DataType::u8, 1}},
            {"s8", {DataType::s8, 1}},
            {"hzn", {DataType::hzn, 12}} };

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
            float scaler = i["scaler"];

            telemetryTypes.push_back({ i["name"], dataType, size, position, scaler });
            position += size;
        }
        return telemetryTypes;
    }
};