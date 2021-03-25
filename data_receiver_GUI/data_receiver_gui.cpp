#include"data_receiver_gui.h"

int main()
{
    DataReceiverGUI gui;
    gui.run();
    gui.receiver.saveAndStop();
}
