#pragma once
#include"forza_horizon4_structure.h"
#include"DataSaverCSV.h"

#include<vector>
#include<deque>
#include<chrono>
#include<atomic>
#include<mutex>
#include<shared_mutex>
#include<asio.hpp>
#include<spdlog/spdlog.h>


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
    asio::steady_timer timeoutDetect{ io };
    asio::io_context::strand strand;

    DataSaverCSV dataSaver;

    DataReceiver(std::chrono::milliseconds dataReservePeriod, short port, asio::ip::address_v4 in_address = asio::ip::make_address_v4("0.0.0.0"))
        :dataReservePeriod(dataReservePeriod),
        currentTime(std::chrono::milliseconds{}),
        port(port),
        endpoint(in_address, port),
        socket(io, endpoint),
        strand(io)
    {
        package_size = sizeof(ForzaHorizon4Data);
        receive_buffer.resize(package_size);

        std::shared_ptr<std::vector<ForzaHorizon4Data>> tmp{ new std::vector<ForzaHorizon4Data>{} };
        tmp->resize(1);
        tmp->reserve(1024);
        data.push_back(std::move(tmp));
    }

    ForzaHorizon4Data getLastData()
    {
        std::shared_lock lock(dataMutex);
        return data.back()->back();
    }

    void receivePackage()
    {
        using namespace std::chrono_literals;

        while (continueReceiveData)
        {
            asio::ip::udp::endpoint endpoint;
            asio::error_code err_code;
            size_t len = socket.receive_from(asio::buffer(receive_buffer), endpoint, 0, err_code);
            if (err_code)
            {
                spdlog::info("{}", err_code.message());
                continue;
            }

            if (len != sizeof(ForzaHorizon4Data))
            {
                spdlog::critical("Package size don't match, is this client out of date? Package size:{}, datapack size:{}", len, sizeof(ForzaHorizon4Data));
                continue;
            }

            ForzaHorizon4Data* receivedPackage = reinterpret_cast<ForzaHorizon4Data*>(receive_buffer.data());
            currentTime = std::chrono::milliseconds(receivedPackage->convertTimestampMS());
            if (receivedPackage->convertCurrentEngineRpm() < 100.0f)
            {
                continue;//forza horizon 4 will send empty packages when in menu, ignore this
            }

            std::unique_lock lock(dataMutex);
            if (data.back()->size() == 1024)
            {
                std::shared_ptr<asio::steady_timer> timer(new asio::steady_timer{ io });
                timer->expires_after(std::chrono::seconds(10));
                timer->async_wait(strand.wrap([this, timer](const asio::error_code& error) {
                    std::shared_ptr<std::vector<ForzaHorizon4Data>> dataToSave;
                    {
                        std::unique_lock readAndSave{ dataMutex };
                        dataToSave = data.front();
                        data.pop_front();
                    }
                    dataSaver.saveData(dataToSave);
                    }));

                std::shared_ptr<std::vector<ForzaHorizon4Data>> tmp{ new std::vector<ForzaHorizon4Data>{} };
                tmp->reserve(1024);
                data.push_back(std::move(tmp));
            }
            data.back()->push_back(*receivedPackage);
        }
    }

    void start()
    {
        continueReceiveData = true;
        dataSaver.createFile("Forza Horizon 4 ");
        io.post([this] {receivePackage(); });

        for (size_t i = 0; i < 4; i++)
        {
            io_context_thread_pool.push_back(std::thread{ [this] {io.run(); } });
        }
    }

    void saveAndStop()
    {
        using namespace std::chrono_literals;
        continueReceiveData = false;
        socket.cancel();
        for (auto& i : io_context_thread_pool)
        {
            i.join();
        }
        io_context_thread_pool.clear();
        std::unique_lock saveLock(dataMutex);

        for (auto& i : data)
        {
            dataSaver.saveData(i);
        }
        dataSaver.close();

        data.clear();
        std::shared_ptr<std::vector<ForzaHorizon4Data>> tmp{ new std::vector<ForzaHorizon4Data>{} };
        tmp->resize(1);
        tmp->reserve(1024);
        data.push_back(std::move(tmp));
    }

    template<typename PlotCallback>
    void drawPlot(PlotCallback&& callback)
    {
        std::shared_lock readLock(dataMutex);
        for (auto& i : data)
        {
            callback(i->data(), i->size());
        }
    }

private:
    std::vector<int8_t> receive_buffer;

    std::deque<std::shared_ptr<std::vector<ForzaHorizon4Data>>> data;
    std::shared_mutex dataMutex;
};