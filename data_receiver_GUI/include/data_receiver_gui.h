#include"forza_horizon4_structure.h"
#include"data_receiver.h"
#include"plot_function_utilities.h"

#include<fmt/format.h>
#include<Mahi/Gui.hpp>
#include<Mahi/Util.hpp>

#include<string_view>

class DataReceiverGUI :public mahi::gui::Application
{
public:
    DataReceiver receiver;
    DataReceiverGUI() :receiver(std::chrono::seconds(10), 9999), Application(1200, 800, "hello")
    {
        ImGui::GetIO().FontGlobalScale = 1.4f;

        receiver.start();
    }

    template<typename DrawFunc>
    inline void drawSimpleXYPlot(std::string_view chartName, std::string_view xLabel, std::string_view yLabel, ImVec2 size, DrawFunc&& drawFunc, double ymin, double ymax)
    {
        using namespace std::chrono_literals;
        //ImPlot::ShowMetricsWindow();

        std::chrono::milliseconds xLimitMax = receiver.currentTime.load();
        std::chrono::milliseconds xLimitMin = xLimitMax - 10s;
        ImPlot::SetNextPlotLimitsY(ymin, ymax, ImGuiCond_Once);
        ImPlot::SetNextPlotLimitsX(static_cast<double>(xLimitMin.count()), static_cast<double>(xLimitMax.count()), ImGuiCond_Always);
        if (ImPlot::BeginPlot(chartName.data(), xLabel.data(), yLabel.data(), size))
        {
            receiver.drawPlot(std::forward<DrawFunc>(drawFunc));
            ImPlot::EndPlot();
        }
    }

    template<typename MainFunc>
    inline void drawFourRowTablePlot(std::string_view tableName, ImVec2 size, std::vector<std::string> columnNames, MainFunc&& func)
    {
        if (ImGui::BeginTable(tableName.data(), 3, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_RowBg, size))
        {
            auto end = columnNames.end() - 1;
            for (auto begin = columnNames.begin(); begin < end; begin++)
            {
                ImGui::TableSetupColumn(begin->c_str(), ImGuiTableColumnFlags_WidthFixed, 180.0f);
            }
            ImGui::TableSetupColumn(columnNames.back().c_str());
            ImGui::TableHeadersRow();

            func();
            ImGui::EndTable();
        }
    }

    virtual void update() override
    {
        if (ImGui::Begin("Options"))
        {
            std::string currentStatus = fmt::format("current status: {}", receiver.continueReceiveData.load());
            ImGui::Text(currentStatus.c_str());
            if (ImGui::Button("start") && receiver.continueReceiveData.load() == false)
            {
                receiver.start();
            }
            if (ImGui::Button("stop") && receiver.continueReceiveData.load() == true)
            {
                receiver.saveAndStop();
            }
        }
        ImGui::End();



        if (ImGui::Begin("Speed Plot"))
        {
            drawSimpleXYPlot("Speed", "time(ms)", "speed(mph)", ImVec2(-1, -1),
                [](ForzaHorizon4Data* data, size_t size) {
                    ImPlot::SetNextLineStyle(IMPLOT_AUTO_COL, 3.0f);
                    ImPlot::PlotLineG("Speed", TimeStampBasedGetterFunc<&ForzaHorizon4Data::convertSpeed>, data, static_cast<int>(size));
                }, 0.0, 300.0);
        }
        ImGui::End();

        if (ImGui::Begin("Tire Temperature Plot"))
        {
            drawFourRowTablePlot("Tire Temperature Plot", ImVec2(-1, 0), { "Tire","Temperature","Plot" }, [this] {
                using namespace std::chrono_literals;
                std::chrono::milliseconds xLimitMax = receiver.currentTime.load();
                std::chrono::milliseconds xLimitMin = xLimitMax - 10s;

                auto last = receiver.getLastData();

                auto PlotTempRow = [this, xLimitMax, xLimitMin](const std::string& rowName, const std::string& rowFormat, auto rowValue, const std::string& tableName, auto GetterFunc)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text(rowName.c_str());
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text(rowFormat.c_str(), rowValue);
                    ImGui::TableSetColumnIndex(2);
                    ImPlot::SetNextPlotLimitsX(static_cast<double>(xLimitMin.count()), static_cast<double>(xLimitMax.count()), ImGuiCond_Always);
                    ImPlot::SetNextPlotLimitsY(0.0, 200.0, ImGuiCond_Always);
                    if (ImPlot::BeginPlot(tableName.c_str(), "time", "temp", ImVec2(-1, 120), ImPlotFlags_CanvasOnly | ImPlotFlags_NoChild, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations))
                    {
                        receiver.drawPlot([GetterFunc, &tableName](ForzaHorizon4Data* data, size_t size)
                            {
                                ImPlot::SetNextLineStyle(IMPLOT_AUTO_COL, 3.0f);
                                ImPlot::PlotLineG(tableName.c_str(), GetterFunc, data, static_cast<int>(size));
                            });
                        ImPlot::EndPlot();
                    }
                };

                PlotTempRow("FrontLeft", "%f F", last.convertTireTempFrontLeft(), "Front Left Tire Temp", TimeStampBasedGetterFunc<&ForzaHorizon4Data::convertTireTempFrontLeft>);
                PlotTempRow("FrontRight", "%f F", last.convertTireTempFrontRight(), "Front Right Tire Temp", TimeStampBasedGetterFunc<&ForzaHorizon4Data::convertTireTempFrontRight>);
                PlotTempRow("RearLeft", "%f F", last.convertTireTempRearLeft(), "Rear Left Tire Temp", TimeStampBasedGetterFunc<&ForzaHorizon4Data::convertTireTempRearLeft>);
                PlotTempRow("RearRight", "%f F", last.convertTireTempRearRight(), "Rear Right Tire Temp", TimeStampBasedGetterFunc<&ForzaHorizon4Data::convertTireTempRearRight>);

                });
        }
        ImGui::End();

        if (ImGui::Begin("Accel and Brake"))
        {
            drawSimpleXYPlot("Accel and Brake", "time(ms)", "pressure", ImVec2(-1, -1),
                [](ForzaHorizon4Data* data, size_t size)
                {
                    ImPlot::SetNextLineStyle(IMPLOT_AUTO_COL, 3.0f);
                    ImPlot::PlotLineG("Accel", TimeStampBasedGetterFunc<&ForzaHorizon4Data::convertAccel>, data, static_cast<int>(size));
                    ImPlot::SetNextLineStyle(IMPLOT_AUTO_COL, 3.0f);
                    ImPlot::PlotLineG("Brake", TimeStampBasedGetterFunc<&ForzaHorizon4Data::convertBrake>, data, static_cast<int>(size));
                }, 0.0, 260.0);
        }
        ImGui::End();
    }
};