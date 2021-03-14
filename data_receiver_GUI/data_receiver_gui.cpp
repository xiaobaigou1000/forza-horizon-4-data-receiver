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
        Application(1200, 900, "Data Receiver")
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
                currentDataArrayPosition = 0;
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
        auto endTimePoint = beginTimePoint;
        if (currentDataArrayPosition != 0)
        {
            endTimePoint = data.back()[(size_t)currentDataArrayPosition - 1].TimestampMS;
        }
        else
        {
            endTimePoint = (data.end() - 1)->back().TimestampMS;
        }

        ImPlot::SetNextPlotLimitsY(0.0, 300.0, ImGuiCond_Always);
        ImPlot::SetNextPlotLimitsX(beginTimePoint, endTimePoint, ImGuiCond_Always);
        auto itemSize = ImGui::GetItemRectSize();
        if (ImPlot::BeginPlot("Speed(MPH)", "x", "f(x)", ImVec2(-1, -1)))
        {
            auto getter = [](void* data, int idx)
            {
                ForzaHorizon4Data* fhd = reinterpret_cast<ForzaHorizon4Data*>(data);
                double x = (fhd + idx)->convertTimestampMS();
                double y = (fhd + idx)->convertSpeed();
                return ImPlotPoint(x, y);
            };

            auto end = data.end() - 1;
            for (auto i = data.begin(); i < end; i++)
            {
                ImPlot::SetNextLineStyle(ImVec4(1, 1, 0, 1), 3.0f);
                ImPlot::PlotLineG("Speed", getter, i->data(), 1024);
            }

            ImPlot::SetNextLineStyle(ImVec4(1, 1, 0, 1), 3.0f);
            ImPlot::PlotLineG("Speed", getter, data.back().data(), currentDataArrayPosition);

            ImPlot::EndPlot();
        }
        ImGui::End();

        ImGui::Begin("Tire Temperature");
        static ImGuiTableFlags flags = ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_RowBg;
        if (ImGui::BeginTable("Tire temp", 3, flags, ImVec2(-1, 0))) {
            ImGui::TableSetupColumn("Tire", ImGuiTableColumnFlags_WidthFixed, 180.0f);
            ImGui::TableSetupColumn("Temperature", ImGuiTableColumnFlags_WidthFixed, 180.0f);
            ImGui::TableSetupColumn("Plot");
            ImGui::TableHeadersRow();

            auto frontLeftTireTempGetter = [](void* data, int idx)
            {
                ForzaHorizon4Data* fhd = reinterpret_cast<ForzaHorizon4Data*>(data);
                double x = (fhd + idx)->convertTimestampMS();
                double y = (fhd + idx)->convertTireTempFrontLeft();
                return ImPlotPoint(x, y);
            };

            auto frontRightTireTempGetter = [](void* data, int idx)
            {
                ForzaHorizon4Data* fhd = reinterpret_cast<ForzaHorizon4Data*>(data);
                double x = (fhd + idx)->convertTimestampMS();
                double y = (fhd + idx)->convertTireTempFrontRight();
                return ImPlotPoint(x, y);
            };

            auto rearLeftTireTempGetter = [](void* data, int idx)
            {
                ForzaHorizon4Data* fhd = reinterpret_cast<ForzaHorizon4Data*>(data);
                double x = (fhd + idx)->convertTimestampMS();
                double y = (fhd + idx)->convertTireTempRearLeft();
                return ImPlotPoint(x, y);
            };

            auto rearRightTireTempGetter = [](void* data, int idx)
            {
                ForzaHorizon4Data* fhd = reinterpret_cast<ForzaHorizon4Data*>(data);
                double x = (fhd + idx)->convertTimestampMS();
                double y = (fhd + idx)->convertTireTempRearRight();
                return ImPlotPoint(x, y);
            };

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Front Left");
            ImGui::TableSetColumnIndex(1);
            if (currentDataArrayPosition == 0)
                ImGui::Text("%f F", (data.end() - 1)->back().convertTireTempFrontLeft());
            else
                ImGui::Text("%f F", data.back()[currentDataArrayPosition-1].convertTireTempFrontLeft());
            ImGui::TableSetColumnIndex(2);
            ImPlot::SetNextPlotLimitsY(0.0, 200.0, ImGuiCond_Always);
            ImPlot::SetNextPlotLimitsX(beginTimePoint, endTimePoint, ImGuiCond_Always);
            if (ImPlot::BeginPlot("Tire Temperature front left", "time", "temp", ImVec2(-1, 100), ImPlotFlags_CanvasOnly | ImPlotFlags_NoChild, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations))
            {
                auto end = data.end() - 1;
                for (auto i = data.begin(); i < end; i++)
                {
                    ImPlot::SetNextLineStyle(ImVec4(1, 1, 0, 1), 3.0f);
                    ImPlot::PlotLineG("TireTempFrontLeft", frontLeftTireTempGetter, i->data(), 1024);
                }

                ImPlot::SetNextLineStyle(ImVec4(1, 1, 0, 1), 3.0f);
                ImPlot::PlotLineG("TireTempFrontLeft", frontLeftTireTempGetter, data.back().data(), currentDataArrayPosition);
                ImPlot::EndPlot();
            }

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Front Right");
            ImGui::TableSetColumnIndex(1);
            if (currentDataArrayPosition == 0)
                ImGui::Text("%f F", (data.end() - 1)->back().convertTireTempFrontRight());
            else
                ImGui::Text("%f F", data.back()[currentDataArrayPosition-1].convertTireTempFrontRight());
            ImGui::TableSetColumnIndex(2);
            ImPlot::SetNextPlotLimitsY(0.0, 200.0, ImGuiCond_Always);
            ImPlot::SetNextPlotLimitsX(beginTimePoint, endTimePoint, ImGuiCond_Always);
            if (ImPlot::BeginPlot("Tire Temperature front right", "time", "temp", ImVec2(-1, 100), ImPlotFlags_CanvasOnly | ImPlotFlags_NoChild, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations))
            {
                auto end = data.end() - 1;
                for (auto i = data.begin(); i < end; i++)
                {
                    ImPlot::SetNextLineStyle(ImVec4(1, 1, 0, 1), 3.0f);
                    ImPlot::PlotLineG("TireTempFrontRight", frontRightTireTempGetter, i->data(), 1024);
                }

                ImPlot::SetNextLineStyle(ImVec4(1, 1, 0, 1), 3.0f);
                ImPlot::PlotLineG("TireTempFrontRight", frontRightTireTempGetter, data.back().data(), currentDataArrayPosition);
                ImPlot::EndPlot();
            }

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Rear Left");
            ImGui::TableSetColumnIndex(1);
            if (currentDataArrayPosition == 0)
                ImGui::Text("%f F", (data.end() - 1)->back().convertTireTempRearLeft());
            else
                ImGui::Text("%f F", data.back()[currentDataArrayPosition-1].convertTireTempRearLeft());
            ImGui::TableSetColumnIndex(2);
            ImPlot::SetNextPlotLimitsY(0.0, 200.0, ImGuiCond_Always);
            ImPlot::SetNextPlotLimitsX(beginTimePoint, endTimePoint, ImGuiCond_Always);
            if (ImPlot::BeginPlot("Tire Temperature rear left", "time", "temp", ImVec2(-1, 100), ImPlotFlags_CanvasOnly | ImPlotFlags_NoChild, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations))
            {
                auto end = data.end() - 1;
                for (auto i = data.begin(); i < end; i++)
                {
                    ImPlot::SetNextLineStyle(ImVec4(1, 1, 0, 1), 3.0f);
                    ImPlot::PlotLineG("TireTempRearLeft", rearLeftTireTempGetter, i->data(), 1024);
                }

                ImPlot::SetNextLineStyle(ImVec4(1, 1, 0, 1), 3.0f);
                ImPlot::PlotLineG("TireTempRearLeft", rearLeftTireTempGetter, data.back().data(), currentDataArrayPosition);
                ImPlot::EndPlot();
            }

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Rear Right");
            ImGui::TableSetColumnIndex(1);
            if (currentDataArrayPosition == 0)
                ImGui::Text("%f F", (data.end() - 1)->back().convertTireTempRearRight());
            else
                ImGui::Text("%f F", data.back()[currentDataArrayPosition-1].convertTireTempRearRight());
            ImGui::TableSetColumnIndex(2);
            ImPlot::SetNextPlotLimitsY(0.0, 200.0, ImGuiCond_Always);
            ImPlot::SetNextPlotLimitsX(beginTimePoint, endTimePoint, ImGuiCond_Always);
            if (ImPlot::BeginPlot("Tire Temperature rear right", "time", "temp", ImVec2(-1, 100), ImPlotFlags_CanvasOnly | ImPlotFlags_NoChild, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations))
            {
                auto end = data.end() - 1;
                for (auto i = data.begin(); i < end; i++)
                {
                    ImPlot::SetNextLineStyle(ImVec4(1, 1, 0, 1), 3.0f);
                    ImPlot::PlotLineG("TireTempRearRight", rearRightTireTempGetter, i->data(), 1024);
                }

                ImPlot::SetNextLineStyle(ImVec4(1, 1, 0, 1), 3.0f);
                ImPlot::PlotLineG("TireTempRearRight", rearRightTireTempGetter, data.back().data(), currentDataArrayPosition);
                ImPlot::EndPlot();
            }

            ImGui::EndTable();
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
