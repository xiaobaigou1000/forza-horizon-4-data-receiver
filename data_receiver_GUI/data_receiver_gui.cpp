#include"forza_horizon4_structure.h"
#include"data_receiver.h"
#include"plot_function_utilities.h"

#include<fmt/format.h>
#include<Mahi/Gui.hpp>
#include<Mahi/Util.hpp>

class DataReceiverGUI :public mahi::gui::Application
{
public:
    DataReceiver receiver;
    DataReceiverGUI() :receiver(std::chrono::seconds(10), 9999), Application(1200, 800, "hello")
    {
        ImGui::GetIO().FontGlobalScale = 1.4f;

        receiver.start();
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
            using namespace std::chrono_literals;
            //ImPlot::ShowMetricsWindow();

            std::chrono::milliseconds xLimitMax = receiver.currentTime.load();
            std::chrono::milliseconds xLimitMin = xLimitMax - 10s;
            ImPlot::SetNextPlotLimitsY(0.0, 300.0, ImGuiCond_Once);
            ImPlot::SetNextPlotLimitsX(xLimitMin.count(), xLimitMax.count(), ImGuiCond_Always);
            ImPlot::BeginPlot("Speed","time(ms)","speed(mph)",ImVec2(-1,-1));

            receiver.drawPlot([](ForzaHorizon4Data* data, size_t size) {
                ImPlot::SetNextLineStyle(ImVec4(34.0/255.0, 131.0/255.0, 188.0 / 255.0, 1), 3.0f);
                ImPlot::PlotLineG("Speed", MyGetterFunc<&ForzaHorizon4Data::convertTimestampMS, &ForzaHorizon4Data::convertSpeed>, data, size);
                });

            ImPlot::EndPlot();
        }
        ImGui::End();
    }
};

int main()
{
    DataReceiverGUI gui;
    gui.run();
}
