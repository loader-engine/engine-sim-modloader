
#include "../../include/loader/luad.h"
#include "../../include/engine_sim_application.h"
#include "../../include/utilities.h"
#include "../../include/lua/lua.hpp"

namespace fs = std::filesystem;

/*
void EngineSimApplication::luaUI_setColors(lua_State* lua)
{
    SetPink(PinkR, PinkG, PinkB);
    SetGreen(GreenR, GreenG, GreenB);
    SetYellow(YellowR, YellowG, YellowB);
    SetRed(RedR, RedG, RedB);
    SetOrange(OrangeR, OrangeG, OrangeB);
    SetBlue(BlueR, BlueG, BlueB);

    Logger::DebugLine("Setting colors...");
}
*/

int process_handlers[100];
int start_handlers[100];
int tick_handlers[100];

int numProcessHandlers = 0;
int numStartHandlers = 0;
int numTickHandlers = 0;

static int addInputHandler(lua_State* L) {
    if (!lua_isfunction(L, 1)) {
        luaL_argerror(L, 1, "expected function");
    }
    lua_pushvalue(L, -1);
    process_handlers[numProcessHandlers++] = luaL_ref(L, LUA_REGISTRYINDEX);
    Logger::DebugLine("added handler for processing");

    return 0;
}

void EngineSimApplication::luaProcess(float dt) {

    luaSetupVars();
    luaSetupEngineVars(false);

    int i;
    for (i = 0; i < numProcessHandlers; ++i) {
        lua_rawgeti(luad::data::L, LUA_REGISTRYINDEX, process_handlers[i]);
        lua_pushnumber(luad::data::L, dt);
        lua_pcall(luad::data::L, 1, 0, 0);
    }

    luaGetEngineVars();
}

static int addStartHandler(lua_State* L) {
    if (!lua_isfunction(L, 1)) {
        luaL_argerror(L, 1, "expected function");
    }
    lua_pushvalue(L, -1);
    start_handlers[numStartHandlers++] = luaL_ref(L, LUA_REGISTRYINDEX);
    Logger::DebugLine("added handler for start");

    return 0;
}

void EngineSimApplication::luaStart() {

    luaSetupVars();
    luaSetupEngineVars(true);

    int i;
    for (i = 0; i < numStartHandlers; ++i) {
        lua_rawgeti(luad::data::L, LUA_REGISTRYINDEX, start_handlers[i]);
        lua_pcall(luad::data::L, 0, 0, 0);
    }

    //luaGetUiVars();
}

static int addTickHandler(lua_State* L) {
    if (!lua_isfunction(L, 1)) {
        luaL_argerror(L, 1, "expected function");
    }
    lua_pushvalue(L, -1);
    tick_handlers[numTickHandlers++] = luaL_ref(L, LUA_REGISTRYINDEX);
    Logger::DebugLine("added handler for tick");

    return 0;
}

void EngineSimApplication::luaTick(float dt) {
    int i;
    for (i = 0; i < numStartHandlers; ++i) {
        lua_rawgeti(luad::data::L, LUA_REGISTRYINDEX, start_handlers[i]);
        lua_pcall(luad::data::L, 0, 0, 0);
    }
}

void EngineSimApplication::luaSetupVars() {
    std::string s = "INPUT_Q";

    s = "INPUT_1";
    luaSetInVar(ysKey::Code::N1, &s);

    s = "INPUT_2";
    luaSetInVar(ysKey::Code::N2, &s);

    s = "INPUT_3";
    luaSetInVar(ysKey::Code::N3, &s);

    s = "INPUT_4";
    luaSetInVar(ysKey::Code::N4, &s);

    s = "INPUT_5";
    luaSetInVar(ysKey::Code::N5, &s);

    s = "INPUT_6";
    luaSetInVar(ysKey::Code::N6, &s);

    s = "INPUT_7";
    luaSetInVar(ysKey::Code::N7, &s);

    s = "INPUT_8";
    luaSetInVar(ysKey::Code::N8, &s);

    s = "INPUT_9";
    luaSetInVar(ysKey::Code::N9, &s);

    s = "INPUT_0";
    luaSetInVar(ysKey::Code::N0, &s);


    s = "INPUT_Q";
    luaSetInVar(ysKey::Code::Q, &s);

    s = "INPUT_W";
    luaSetInVar(ysKey::Code::W, &s);

    s = "INPUT_E";
    luaSetInVar(ysKey::Code::E, &s);

    s = "INPUT_R";
    luaSetInVar(ysKey::Code::R, &s);

    s = "INPUT_T";
    luaSetInVar(ysKey::Code::T, &s);

    s = "INPUT_Y";
    luaSetInVar(ysKey::Code::Y, &s);

    s = "INPUT_U";
    luaSetInVar(ysKey::Code::U, &s);

    s = "INPUT_I";
    luaSetInVar(ysKey::Code::I, &s);

    s = "INPUT_O";
    luaSetInVar(ysKey::Code::O, &s);

    s = "INPUT_P";
    luaSetInVar(ysKey::Code::P, &s);


    s = "INPUT_A";
    luaSetInVar(ysKey::Code::A, &s);

    s = "INPUT_S";
    luaSetInVar(ysKey::Code::S, &s);

    s = "INPUT_D";
    luaSetInVar(ysKey::Code::D, &s);

    s = "INPUT_F";
    luaSetInVar(ysKey::Code::F, &s);

    s = "INPUT_G";
    luaSetInVar(ysKey::Code::G, &s);

    s = "INPUT_H";
    luaSetInVar(ysKey::Code::H, &s);

    s = "INPUT_J";
    luaSetInVar(ysKey::Code::J, &s);

    s = "INPUT_K";
    luaSetInVar(ysKey::Code::K, &s);

    s = "INPUT_L";
    luaSetInVar(ysKey::Code::L, &s);


    s = "INPUT_Z";
    luaSetInVar(ysKey::Code::Z, &s);

    s = "INPUT_X";
    luaSetInVar(ysKey::Code::X, &s);

    s = "INPUT_C";
    luaSetInVar(ysKey::Code::C, &s);

    s = "INPUT_V";
    luaSetInVar(ysKey::Code::V, &s);

    s = "INPUT_B";
    luaSetInVar(ysKey::Code::B, &s);

    s = "INPUT_N";
    luaSetInVar(ysKey::Code::N, &s);

    s = "INPUT_M";
    luaSetInVar(ysKey::Code::M, &s);
}

void EngineSimApplication::luaSetInVar(ysKey::Code code, std::string* name) {
    if (m_engine.IsKeyDown(code))
        luad::utils::luaSetVar(*name, "true");
    else
        luad::utils::luaSetVar(*name, "false");
}

void EngineSimApplication::luaSetupEngineVars(bool start) {
    if (!start) {
        Engine* engine = m_simulator.getEngine();
        if (engine != nullptr) {
            luad::utils::luaSetVar("Engine_Name", engine->getName());

            luad::utils::luaSetVar("Engine_RPM", std::to_string(engine->getRpm()));
            luad::utils::luaSetVar("Engine_AFR", std::to_string(engine->getIntakeAfr()));
            luad::utils::luaSetVar("Engine_Throttle", std::to_string(engine->getThrottle()));
            luad::utils::luaSetVar("Engine_ManifoldPressure", std::to_string(engine->getManifoldPressure()));

            // get avg exhaust airflow
            double avg = 0;
            int i = 0;
            for (i = 0; i < engine->getExhaustSystemCount(); i++) {
                avg += engine->getExhaustSystem(i)->getFlow();
            }
            avg /= i;

            luad::utils::luaSetVar("Engine_ExhaustFlow", std::to_string(avg));

            avg = 0;
            i = 0;
            for (i = 0; i < engine->getIntakeCount(); i++) {
                avg += engine->getIntake(i)->m_flow;
            }
            avg /= i;

            luad::utils::luaSetVar("Engine_IntakeFlow", std::to_string(avg));

            double* ratios = getSimulator()->getTransmission()->m_gearRatios;
            luad::utils::luaSetVar("Engine_Gear1", std::to_string(ratios[0]));
            luad::utils::luaSetVar("Engine_Gear2", std::to_string(ratios[1]));
            luad::utils::luaSetVar("Engine_Gear3", std::to_string(ratios[2]));
            luad::utils::luaSetVar("Engine_Gear4", std::to_string(ratios[3]));
            luad::utils::luaSetVar("Engine_Gear5", std::to_string(ratios[4]));
            luad::utils::luaSetVar("Engine_Gear6", std::to_string(ratios[5]));

            luad::utils::luaSetVar("Simulator_FPS", std::to_string(m_engine.GetAverageFramerate()));
        }
    }
    
    luad::utils::luaSetVar("Loader_Version", getModLoaderVersion());
    luad::utils::luaSetVar("Loader_Sim_Version", getBuildVersion());
    //free(engine);
}

void EngineSimApplication::luaGetEngineVars() {
    std::string result = "";
    Engine* engine = m_simulator.getEngine();

    result = luad::utils::luaGetVar("Engine_Throttle");
    double throt = std::stod(result);
    engine->setThrottle(throt);

    result = luad::utils::luaGetVar("Engine_ManifoldPressure");
    double press = std::stod(result);
    //for (int i = 0; engine->getIntakeCount(); i++) {
    //    //Simulator* sim = &m_simulator;
    //    //sim->getEngine()->getIntake(i)->addPress = press;
    //}
    //engine->press = press;
    //Logger::DebugLine("setting intake press: " + result);

    result = luad::utils::luaGetVar("Engine_IntakeFlow");
    double flow = std::stod(result);
    //engine->flow = flow;
    //Logger::DebugLine("setting intake flow: " + result);
    
    //double res[5] = {};
    //result = luad::utils::luaGetVar("Engine_Gear1");
    //res[0] = std::stod(result);
    //result = luad::utils::luaGetVar("Engine_Gear2");
    //res[1] = std::stod(result);
    //result = luad::utils::luaGetVar("Engine_Gear3");
    //res[2] = std::stod(result);
    //result = luad::utils::luaGetVar("Engine_Gear4");
    //res[3] = std::stod(result);
    //result = luad::utils::luaGetVar("Engine_Gear5");
    //res[4] = std::stod(result);
    //result = luad::utils::luaGetVar("Engine_Gear6");
    //res[5] = std::stod(result);

    //getSimulator()->getTransmission()->m_gearRatios = res;

    engine->UpdateShit();

    //free(engine);
}

void EngineSimApplication::luaGetUiVars() {
    
    /*luaSetUiVar("pink");
    luaSetUiVar("green");
    luaSetUiVar("yellow");
    luaSetUiVar("red");
    luaSetUiVar("orange");
    luaSetUiVar("blue");
    */
}

void EngineSimApplication::reloadLua(std::string luaPath) {
    luad::data::reloading = true;
    
    luad::data::reinit();
    loadLua(luaPath, false);

    luad::data::reloading = false;
}

void EngineSimApplication::loadLua(std::string luaPath, bool first) {
    //char buff[256];
    //int error;
    //init is now done in luad::data::init()
    luad::data::init(this);
    s_modAmount = 0;

    if (first) {
        Logger::DebugLine("===============================================================");
        Logger::DebugLine("===============================================================");
        Logger::DebugLine("=========================mod-loader============================");
        Logger::DebugLine("======================loading lua files========================");
        Logger::DebugLine("===============================================================");
        Logger::DebugLine("===============================================================");
    }
    else {
        Logger::DebugLine("Reloading...");
    }

    Logger::DebugLine("Setting up lua functions");

    luad::utils::luaPushFunction("trace", luad::functions::luaTrace);
    luad::utils::luaPushFunction("Cinfo", luad::functions::luaInfo);

    /*
    lua_pushcclosure(luad::data::L, luad::functions::luaSetPink, 0);
    lua_setglobal(luad::data::L, "setPink");
    lua_pushcclosure(luad::data::L, luad::functions::luaSetGreen, 0);
    lua_setglobal(luad::data::L, "setGreen");
    lua_pushcclosure(luad::data::L, luad::functions::luaSetYellow, 0);
    lua_setglobal(luad::data::L, "setYellow");
    lua_pushcclosure(luad::data::L, luad::functions::luaSetRed, 0);
    lua_setglobal(luad::data::L, "setRed");
    lua_pushcclosure(luad::data::L, luad::functions::luaSetOrange, 0);
    lua_setglobal(luad::data::L, "setOrange");
    lua_pushcclosure(luad::data::L, luad::functions::luaSetBlue, 0);
    lua_setglobal(luad::data::L, "setBlue");
    
    lua_pushcclosure(luad::data::L, luad::functions::luaSetVolume, 0);
    lua_setglobal(luad::data::L, "setVolume");
    lua_pushcclosure(luad::data::L, luad::functions::luaSetFrequency, 0);
    lua_setglobal(luad::data::L, "setFrequency");
    */
    luad::utils::luaPushFunction("CsetModel", luad::functions::luaSetModel);
    luad::utils::luaPushFunction("CsetTexture", luad::functions::luaSetTexture);
    luad::utils::luaPushFunction("CloadTexture", luad::functions::luaLoadTexture);

    /*
    lua_pushcclosure(luad::data::L, luad::functions::luaSetTorqueUnit, 0);
    lua_setglobal(luad::data::L, "setTorqueUnit");
    lua_pushcclosure(luad::data::L, luad::functions::luaSetSpeedUnit, 0);
    lua_setglobal(luad::data::L, "setSpeedUnit");
    lua_pushcclosure(luad::data::L, luad::functions::luaSetAirflowUnit, 0);
    lua_setglobal(luad::data::L, "setAirflowUnit");
    lua_pushcclosure(luad::data::L, luad::functions::luaSetPressureUnit, 0);
    lua_setglobal(luad::data::L, "setPressureUnit");
    */

    luad::utils::luaPushFunction("CsetCrankWeight", luad::functions::luaSetCrankWeight);
    luad::utils::luaPushFunction("CsetFlywheelWeight", luad::functions::luaSetFlywheelWeight);
    luad::utils::luaPushFunction("CsetPistonWeight", luad::functions::luaSetPistonWeight);
    luad::utils::luaPushFunction("CsetConrodWeight", luad::functions::luaSetConrodWeight);
    luad::utils::luaPushFunction("CinitDNet", luad::functions::luaInitDNet);

    lua_pushcclosure(luad::data::L, luad::functions::luaAddSynth, 0);
    lua_setglobal(luad::data::L, "CsynthAdd");

    Logger::DebugLine("Setting up lua handlers");
    lua_pushcclosure(luad::data::L, addInputHandler, 0);
    lua_setglobal(luad::data::L, "addProcessHandler");
    lua_pushcclosure(luad::data::L, addStartHandler, 0);
    lua_setglobal(luad::data::L, "addStartHandler");
    lua_pushcclosure(luad::data::L, addTickHandler, 0);
    lua_setglobal(luad::data::L, "addTickHandler");

    Logger::DebugLine("Loading 'loader.lua'...");

    if (fs::exists(m_assetPath + "\\loader.lua")) {
        luaL_dofile(luad::data::L, (m_assetPath + "\\loader.lua").c_str());
    }

    Logger::DebugLine("Loaded 'loader.lua'.");

    Logger::DebugLine("Loading files...");

    for (const auto& entry : fs::directory_iterator(luaPath)) {
        std::string path = entry.path().string();
        if (path != luaPath + "\\preConfig.lua" && path != luaPath + "\\config.lua")
        {
            Logger::DebugLine("Loading file: " + path);
            //luaL_loadfile(luad::data::L, pathChar);
            luaL_dofile(luad::data::L, path.c_str());
            s_modAmount++;
        }
    }

    Logger::DebugLine("Loading preConfig...");
    if (fs::exists(luaPath + "\\preConfig.lua")) {

        // prepare for compiling file
        //luaSetupEngineVars(true);

        luaL_dofile(luad::data::L, (luaPath + "/preConfig.lua").c_str());

        // Get results
        //luaGetUiVars();

        Logger::DebugLine("PreConfig Loaded");
    }
    else {
        Logger::DebugLine("PreConfig Not loaded: file not found");
    }

    Logger::DebugLine("Warning: Config is loaded after first initialize()!");

    Logger::DebugLine("Loaded!");
}

void EngineSimApplication::luaLoadConfig(std::string luaPath) {
    Logger::DebugLine("Loading config...");

    if (fs::exists(luaPath + "\\config.lua")) {

        // prepare for compiling file
        //luaSetupEngineVars(true);

        luaL_dofile(luad::data::L, (luaPath + "/config.lua").c_str());

        // Get results
        //luaGetUiVars();

        Logger::DebugLine("Config Loaded");
    }
    else {
        Logger::DebugLine("Config Not loaded: file not found");
    }
}

void EngineSimApplication::luaFail(std::string error) {
    Logger::DebugLine(error);
}

void EngineSimApplication::unloadLua() {
    lua_close(luad::data::L);
    luad::functions::endDNet();
}
