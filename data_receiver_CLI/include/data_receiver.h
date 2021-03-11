#pragma once
#include"telemetry_type.h"

#include<asio.hpp>
#include<map>
#include<fmt/printf.h>
#include<fmt/ranges.h>
#include<spdlog/spdlog.h>

class DataReceiver
{
public:
    asio::io_context io_context;
    asio::ip::address_v4 address;
    size_t port;
    asio::ip::udp::endpoint endpoint;
    asio::ip::udp::socket socket;

    DataReceiver(short port, size_t maxDatapackSize = 1024, asio::ip::address_v4 in_address = asio::ip::make_address_v4("0.0.0.0"))
        :port(port),
        endpoint(in_address, port),
        socket(io_context, endpoint)
    {
        datapackBuffer.resize(maxDatapackSize);
    }

    void updateTelemetryTypeInfo(const std::vector<TelemetryType>& source) { telemetryTypes = source; }
    void updateTelemetryTypeInfo(std::vector<TelemetryType>&& source) { telemetryTypes = source; }

    std::tuple<asio::ip::udp::endpoint, size_t> receivePackage()
    {
        asio::ip::udp::endpoint remote_endpoint;
        size_t dataLength = socket.receive_from(asio::buffer(datapackBuffer), remote_endpoint);
        return { remote_endpoint,dataLength };
    }

    inline void receiveAndProcessDataCLI(const TelemetryType engineRPMInfo, const std::vector<TelemetryType>& dataConcerned)
    {
        auto [remote_endpoint, dataLength] = receivePackage();
        spdlog::info("datapack size: {}", dataLength);
        int8_t* dataPointer = datapackBuffer.data();

        float engineRPM = *reinterpret_cast<float*>(dataPointer + engineRPMInfo.position);
        if (engineRPM < 100.0f)
        {
            return;
        }

        std::vector<std::string> dataCache;

        using DataType = TelemetryType::DataType;
        for (const auto& i : dataConcerned)
        {
            std::string value;
            int8_t* dataPosition = dataPointer + i.position;

            switch (i.type)
            {
            case DataType::s32:
                dataCache.push_back(fmt::format("{}: {}", i.name, i.scaler * (*reinterpret_cast<int32_t*>(dataPosition))));
                break;
            case DataType::u32:
                dataCache.push_back(fmt::format("{}: {}", i.name, i.scaler * (*reinterpret_cast<uint32_t*>(dataPosition))));
                break;
            case DataType::f32:
                dataCache.push_back(fmt::format("{}: {}", i.name, i.scaler * (*reinterpret_cast<float*>(dataPosition))));
                break;
            case DataType::s8:
                dataCache.push_back(fmt::format("{}: {}", i.name, i.scaler * (*reinterpret_cast<int8_t*>(dataPosition))));
                break;
            case DataType::u16:
                dataCache.push_back(fmt::format("{}: {}", i.name, i.scaler * (*reinterpret_cast<uint16_t*>(dataPosition))));
                break;
            case DataType::u8:
                dataCache.push_back(fmt::format("{}: {}", i.name, i.scaler * (*reinterpret_cast<uint8_t*>(dataPosition))));
                break;
            }
        }

        spdlog::info("{}", dataCache);
    }
private:
    std::vector<int8_t> datapackBuffer;
    std::vector<TelemetryType> telemetryTypes;
};
