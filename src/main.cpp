#include "../include/engine_sim_application.h"

#include <iostream>
#include <fstream>

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    (void)nCmdShow;
    (void)lpCmdLine;
    (void)hPrevInstance;

    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    Logger::Initialize();

    bool recording = false;
    int rpm = 0;
    bool on = false;

    std::ifstream paramFile("params.txt");
    std::string line;
    if (paramFile.is_open()) {
        while (std::getline(paramFile, line))
        {
            if (line._Starts_with("rpm=")) {
                //assume we are recording
                recording = true;
                rpm = std::stoi(line.substr(4));
                rpm = units::rpm(rpm - 1000);
            }
            if (line._Starts_with("on")) {
                on = true;
            }
        }
        paramFile.close();
    }
    else {
        Logger::DebugLine("Failed to open params");
    }

    EngineSimApplication application;
    application.initialize((void*)&hInstance, ysContextObject::DeviceAPI::DirectX11);

    if (recording) {
        application.getSimulator()->getEngine()->getIgnitionModule()->m_enabled = true;
        application.getSimulator()->m_dyno.m_enabled = true;
        application.getSimulator()->m_dyno.m_hold = true;
        application.m_dynoSpeed = rpm;
        application.rpmOn = on;
    }
    else {
        application.rpmOn = false;
    }

    application.run();
    application.destroy();
    Logger::Finalize();

    return 0;
}
