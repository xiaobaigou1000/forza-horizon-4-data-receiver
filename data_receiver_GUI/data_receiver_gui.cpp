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
    inline void drawSimpleXYPlot(std::string_view chartName, std::string_view xLabel, std::string_view yLabel, ImVec2 size, DrawFunc&& drawFunc)
    {
        using namespace std::chrono_literals;
        //ImPlot::ShowMetricsWindow();

        std::chrono::milliseconds xLimitMax = receiver.currentTime.load();
        std::chrono::milliseconds xLimitMin = xLimitMax - 10s;
        ImPlot::SetNextPlotLimitsY(0.0, 300.0, ImGuiCond_Once);
        ImPlot::SetNextPlotLimitsX(static_cast<double>(xLimitMin.count()), static_cast<double>(xLimitMax.count()), ImGuiCond_Always);
        ImPlot::BeginPlot(chartName.data(), xLabel.data(), yLabel.data(), size);

        receiver.drawPlot(std::forward<DrawFunc>(drawFunc));
        ImPlot::EndPlot();
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

        if (ImGui::Begin("Test Plot"))
        {
            drawSimpleXYPlot("Speed", "time(ms)", "speed(mph)", ImVec2(-1, -1),
                [](ForzaHorizon4Data* data, size_t size) {
                    ImPlot::SetNextLineStyle(ImVec4(34.0f / 255.0f, 131.0f / 255.0f, 188.0f / 255.0f, 1.0f), 3.0f);
                    ImPlot::PlotLineG("Speed", MyGetterFunc<&ForzaHorizon4Data::convertTimestampMS, &ForzaHorizon4Data::convertSpeed>, data, static_cast<int>(size));
                });
        }
        ImGui::End();
    }
};

int main()
{
    DataReceiverGUI gui;
    gui.run();
    gui.receiver.saveAndStop();
}
