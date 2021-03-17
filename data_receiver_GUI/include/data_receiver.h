#pragma once
#include"forza_horizon4_structure.h"

#include<vector>
#include<deque>
#include<chrono>
#include<atomic>
#include<mutex>
#include<shared_mutex>
#include<asio.hpp>


class DataReceiver
{
public:
    asio::io_context io;
    asio::ip::address_v4 address;
    short port;
    asio::ip::udp::endpoint endpoint;
    asio::ip::udp::socket socket;
    size_t package_size;
    std::vector<std::thread> io_context_thread_pool;
    std::atomic<bool> continueReceiveData{ false };
    std::atomic<std::chrono::milliseconds> currentTime;
    const std::chrono::milliseconds dataReservePeriod;

    DataReceiver(std::chrono::milliseconds dataReservePeriod, short port, asio::ip::address_v4 in_address = asio::ip::make_address_v4("0.0.0.0"))
        :dataReservePeriod(dataReservePeriod),
        currentTime(std::chrono::milliseconds{}),
        port(port),
        endpoint(in_address, port),
        socket(io, endpoint)
    {

        package_size = sizeof(ForzaHorizon4Data);
        receive_buffer.resize(package_size);

        std::vector<ForzaHorizon4Data> tmp;
        tmp.reserve(1024);
        data.push_back(std::move(tmp));
    }

    void receivePackage()
    {
        while (continueReceiveData)
        {
            asio::ip::udp::endpoint endpoint;
            socket.receive_from(asio::buffer(receive_buffer), endpoint);
            ForzaHorizon4Data* receivedPackage = reinterpret_cast<ForzaHorizon4Data*>(receive_buffer.data());
            currentTime = std::chrono::milliseconds(receivedPackage->convertTimestampMS());
            if (receivedPackage->convertCurrentEngineRpm() < 100.0f)
            {
                continue;
            }

            std::unique_lock lock(dataMutex);
            if (data.size() == 3)
            {
                data.pop_front();
            }
            if (data.back().size() == 1024)
            {
                std::shared_ptr<asio::steady_timer> timer(new asio::steady_timer{ io });
                timer->expires_after(std::chrono::seconds(10));
                timer->async_wait([this, timer](const asio::error_code& error) {
                    {
                        std::shared_lock readAndSave{ dataMutex };
                        auto& dataToSave = data.front();
                        //save data here
                    }
                    {
                        std::unique_lock removeSavedData{ dataMutex };
                        data.pop_front();
                    }});

                std::vector<ForzaHorizon4Data> tmp;
                tmp.reserve(1024);
                data.push_back(std::move(tmp));
            }
            data.back().push_back(*receivedPackage);
        }
    }

    void start()
    {
        continueReceiveData = true;
        io.post([this] {receivePackage(); });

        for (size_t i = 0; i < 4; i++)
        {
            io_context_thread_pool.push_back(std::thread{ [this] {io.run(); } });
        }
    }

    void saveAndStop()
    {
        continueReceiveData = false;
        for (auto& i : io_context_thread_pool)
        {
            i.join();
        }
        io_context_thread_pool.clear();
        std::unique_lock saveLock(dataMutex);
        //save data here
        data.clear();
    }

    template<typename PlotCallback>
    void drawPlot(PlotCallback&& callback)
    {
        std::shared_lock readLock(dataMutex);
        for (auto& i : data)
        {
            callback(i.data(), i.size());
        }
    }

private:
    std::vector<int8_t> receive_buffer;

    std::deque<std::vector<ForzaHorizon4Data>> data;
    std::shared_mutex dataMutex;
};