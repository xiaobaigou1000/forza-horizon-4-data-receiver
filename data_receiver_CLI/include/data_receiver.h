#pragma once
#include"telemetry_type.h"
#include"forza_horizon4_structure.h"

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

    DataReceiver(short port, asio::ip::address_v4 in_address = asio::ip::make_address_v4("0.0.0.0"))
        :port(port),
        endpoint(in_address, port),
        socket(io_context, endpoint)
    {
        receive_buffer.resize(sizeof(ForzaHorizon4Data));
    }
    
    inline std::tuple<asio::ip::udp::endpoint, size_t> receivePackage()
    {
        asio::ip::udp::endpoint remote_endpoint;
        size_t dataLength = socket.receive_from(asio::buffer(receive_buffer), remote_endpoint);
        return { remote_endpoint,dataLength };
    }

    inline ForzaHorizon4Data getData()
    {
        auto [endpoint, length] = receivePackage();
        ForzaHorizon4Data result{};
        std::copy(receive_buffer.begin(), receive_buffer.end(), reinterpret_cast<int8_t*>(&result));
        return result;
    }

    void run()
    {
        
        while (true)
        {
            auto result = getData();
            if (result.convertCurrentEngineRpm() < 100.0f)
            {
                continue;
            }
            spdlog::info("Engine RPM: {}, Power: {}, Speed: {}", result.convertCurrentEngineRpm(), result.convertPower(), result.convertSpeed());
        }
    }

private:
    std::vector<int8_t> receive_buffer;
};
