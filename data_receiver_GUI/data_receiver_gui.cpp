#include"forza_horizon4_structure.h"

#include<asio.hpp>
#include<vector>
#include<functional>
#include<deque>
#include<array>
#include<atomic>
#include<memory>
#include<shared_mutex>
#include<fmt/format.h>
#include<Mahi/Gui.hpp>
#include<Mahi/Util.hpp>

class DataReceiverGUI :public mahi::gui::Application
{
public:
    asio::io_context io;
    asio::ip::address_v4 address;
    short port;
    asio::ip::udp::endpoint endpoint;
    asio::ip::udp::socket socket;
    size_t package_size;
    std::vector<std::thread> io_context_thread_pool;

    DataReceiverGUI(short port, asio::ip::address_v4 in_address = asio::ip::make_address_v4("0.0.0.0"))
        :port(port),
        endpoint(in_address, port),
        socket(io, endpoint),
        Application(1200,900,"Data Receiver")
    {
        ImGui::GetIO().FontGlobalScale = 1.4f;

        package_size = sizeof(ForzaHorizon4Data);
        receive_buffer.resize(package_size);

        std::vector<ForzaHorizon4Data> tmp;
        tmp.resize(1024);
        data.push_back(std::move(tmp));

        for (size_t i = 0; i < 4; i++)
        {
            io_context_thread_pool.push_back(std::thread{ [this] {io.run(); } });
        }

        io.post([this] {receivePackage(); });
    }

    void receivePackage()
    {
        while (true)
        {
            asio::ip::udp::endpoint endpoint;
            socket.receive_from(asio::buffer(receive_buffer), endpoint);
            if (reinterpret_cast<ForzaHorizon4Data*>(receive_buffer.data())->convertCurrentEngineRpm() < 100.0f)
            {
                continue;
            }

            if (data.size() == 3)
            {
                std::unique_lock lock(dataMutex);
                data.pop_front();
            }
            if (currentDataArrayPosition == 1024)
            {
                std::unique_lock lock(dataMutex);
                std::vector<ForzaHorizon4Data> tmp;
                tmp.resize(1024);
                data.push_back(std::move(tmp));
            }
            std::copy(receive_buffer.begin(), receive_buffer.end(), reinterpret_cast<int8_t*>(&(data.back()[currentDataArrayPosition])));
            currentDataArrayPosition += 1;
        }
    }

    virtual void update() override
    {
        std::shared_lock lock(dataMutex);

        ImGui::Begin("Basic Data");

        auto beginTimePoint = data.front().front().TimestampMS;
        if (ImPlot::BeginPlot("Line Plot", "x", "f(x)", ImVec2(ImGui::GetItemRectSize().x, 800)))
        {

            auto getter = [](void* data, int idx)
            {
                ForzaHorizon4Data* fhd = reinterpret_cast<ForzaHorizon4Data*>(data);
                double x = idx;
                double y = (fhd + idx)->Speed;
                return ImPlotPoint(x, y);
            };

            auto end = data.end() - 1;
            for (auto i = data.begin(); i < end; i++)
            {
                ImPlot::PlotDigitalG("Speed", getter, i->data(), 1024);
            }

            ImPlot::PlotDigitalG("Speed", getter, data.back().data(), currentDataArrayPosition);

            ImPlot::EndPlot();
        }
        ImGui::End();
    }

private:
    std::vector<int8_t> receive_buffer;
    std::deque<std::vector<ForzaHorizon4Data>> data;
    std::atomic<int32_t> currentDataArrayPosition = 0;

    std::shared_mutex dataMutex;
};

int main()
{
    DataReceiverGUI gui{ 9999 };
    gui.run();
}
