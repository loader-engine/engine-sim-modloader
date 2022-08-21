
#include "..\..\include\engine_sim_application.h"
#include "../../include/utilities.h"

namespace fs = std::filesystem;

static int luaTrace(lua_State* lua)
{
    assert(lua_isstring(lua, 1));

    const char* msg = lua_tostring(lua, 1);
    std::string str(msg);

    // debug output
    Logger::DebugLine("script: " + str);

    return 0;
}

int luaSetPink(lua_State* lua) {
    assert(lua_isnumber(lua, 1));
    assert(lua_isnumber(lua, 2));
    assert(lua_isnumber(lua, 3));

    const int r = (int)lua_tonumber(lua, 1);
    const int g = (int)lua_tonumber(lua, 2);
    const int b = (int)lua_tonumber(lua, 3);
    
    EngineSimApplication::instance->SetPink(r, g, b);

    return 0;
}
int luaSetGreen(lua_State* lua) {
    assert(lua_isnumber(lua, 1));
    assert(lua_isnumber(lua, 2));
    assert(lua_isnumber(lua, 3));

    const int r = (int)lua_tonumber(lua, 1);
    const int g = (int)lua_tonumber(lua, 2);
    const int b = (int)lua_tonumber(lua, 3);

    EngineSimApplication::instance->SetGreen(r, g, b);

    return 0;
}
int luaSetYellow(lua_State* lua) {
    assert(lua_isnumber(lua, 1));
    assert(lua_isnumber(lua, 2));
    assert(lua_isnumber(lua, 3));

    const int r = (int)lua_tonumber(lua, 1);
    const int g = (int)lua_tonumber(lua, 2);
    const int b = (int)lua_tonumber(lua, 3);

    EngineSimApplication::instance->SetYellow(r, g, b);

    return 0;
}
int luaSetRed(lua_State* lua) {
    assert(lua_isnumber(lua, 1));
    assert(lua_isnumber(lua, 2));
    assert(lua_isnumber(lua, 3));

    const int r = (int)lua_tonumber(lua, 1);
    const int g = (int)lua_tonumber(lua, 2);
    const int b = (int)lua_tonumber(lua, 3);

    EngineSimApplication::instance->SetRed(r, g, b);

    return 0;
}
int luaSetOrange(lua_State* lua) {
    assert(lua_isnumber(lua, 1));
    assert(lua_isnumber(lua, 2));
    assert(lua_isnumber(lua, 3));

    const int r = (int)lua_tonumber(lua, 1);
    const int g = (int)lua_tonumber(lua, 2);
    const int b = (int)lua_tonumber(lua, 3);

    EngineSimApplication::instance->SetOrange(r, g, b);

    return 0;
}
int luaSetBlue(lua_State* lua) {
    assert(lua_isnumber(lua, 1));
    assert(lua_isnumber(lua, 2));
    assert(lua_isnumber(lua, 3));

    const int r = (int)lua_tonumber(lua, 1);
    const int g = (int)lua_tonumber(lua, 2);
    const int b = (int)lua_tonumber(lua, 3);

    EngineSimApplication::instance->SetBlue(r, g, b);

    return 0;
}

int luaSetVolume(lua_State* lua) {
    assert(lua_isnumber(lua, 1));

    double volume = (double)lua_tonumber(lua, 1);
    volume /= 100;

    EngineSimApplication::instance->m_engine;
    Synthesizer::AudioParameters audioParams = EngineSimApplication::instance->m_simulator.getSynthesizer()->getAudioParameters();
    audioParams.Volume = clamp(volume);

    EngineSimApplication::instance->m_simulator.getSynthesizer()->setAudioParameters(audioParams);
    //Logger::DebugLine(std::to_string(volume));
    //Logger::DebugLine(std::to_string(audioParams.Volume));

    return 0;
}

int luaSetFrequency(lua_State* lua) {
    assert(lua_isnumber(lua, 1));

    int freq = (int)lua_tonumber(lua, 1);
    freq = clamp(freq, 400.0, 400000.0);

    EngineSimApplication::instance->m_simulator.setSimulationFrequency(freq);

    return 0;
}

int luaSetTorqueUnit(lua_State* lua) {
    assert(lua_isstring(lua, 1));

    const char* type = lua_tostring(lua, 1);
    std::string str(type);

    EngineSimApplication::instance->UNIT_TYPE_TORQUE = str;
    Logger::DebugLine("Set torque unit to: " + str);

    return 0;
}

int luaSetSpeedUnit(lua_State* lua) {
    assert(lua_isstring(lua, 1));

    const char* type = lua_tostring(lua, 1);
    std::string str(type);

    EngineSimApplication::instance->UNIT_TYPE_SPEED = str;
    Logger::DebugLine("Set speed unit to: " + str);

    return 0;
}

int luaSetAirflowUnit(lua_State* lua) {
    assert(lua_isstring(lua, 1));

    const char* type = lua_tostring(lua, 1);
    std::string str(type);

    EngineSimApplication::instance->UNIT_TYPE_AIRFLOW = str;
    Logger::DebugLine("Set airflow unit to: " + str);

    return 0;
}

int luaSetPressureUnit(lua_State* lua) {
    assert(lua_isstring(lua, 1));

    const char* type = lua_tostring(lua, 1);
    std::string str(type);

    EngineSimApplication::instance->UNIT_TYPE_PRESSURE = str;
    Logger::DebugLine("Set pressure unit to: " + str);

    return 0;
}

EngineSimApplication* ap;

static int luaInfo(lua_State* lua)
{
    assert(lua_isstring(lua, 1));

    const char* msg = lua_tostring(lua, 1);
    std::string str(msg);

    // debug output
    ap->m_infoCluster->setLogMessage(msg);

    return 0;
}

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

int numProcessHandlers = 0;
int numStartHandlers = 0;

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
        lua_rawgeti(L, LUA_REGISTRYINDEX, process_handlers[i]);
        lua_pushnumber(L, dt);
        lua_pcall(L, 1, 0, 0);
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
        lua_rawgeti(L, LUA_REGISTRYINDEX, start_handlers[i]);
        lua_pcall(L, 0, 0, 0);
    }

    //luaGetUiVars();
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
    const int len = name->length();
    char* nameChar = (char*)malloc(len + 1);
    strcpy(nameChar, name->c_str());

    if (m_engine.IsKeyDown(code))
        lua_pushstring(L, "true");
    else
        lua_pushstring(L, "false");

    lua_setglobal(L, nameChar);

    free(nameChar);
}

void EngineSimApplication::luaSetupEngineVars(bool start) {

    // ui shit
    luaSetVar("UI_pink_R", std::to_string(PinkR));
    luaSetVar("UI_pink_G", std::to_string(PinkG));
    luaSetVar("UI_pink_B", std::to_string(PinkB));

    luaSetVar("UI_green_R", std::to_string(GreenR));
    luaSetVar("UI_green_G", std::to_string(GreenG));
    luaSetVar("UI_green_B", std::to_string(GreenB));

    luaSetVar("UI_yellow_R", std::to_string(YellowR));
    luaSetVar("UI_yellow_G", std::to_string(YellowG));
    luaSetVar("UI_yellow_B", std::to_string(YellowB));

    luaSetVar("UI_red_R", std::to_string(RedR));
    luaSetVar("UI_red_G", std::to_string(RedG));
    luaSetVar("UI_red_B", std::to_string(RedB));

    luaSetVar("UI_orange_R", std::to_string(OrangeR));
    luaSetVar("UI_orange_G", std::to_string(OrangeG));
    luaSetVar("UI_orange_B", std::to_string(OrangeB));

    luaSetVar("UI_blue_R", std::to_string(BlueR));
    luaSetVar("UI_blue_G", std::to_string(BlueG));
    luaSetVar("UI_blue_B", std::to_string(BlueB));

    if (!start) {
        Engine* engine = m_simulator.getEngine();
        luaSetVar("Engine_Name", engine->getName());

        luaSetVar("Engine_RPM", std::to_string(engine->getRpm()));
        luaSetVar("Engine_AFR", std::to_string(engine->getIntakeAfr()));
        luaSetVar("Engine_Throttle", std::to_string(engine->getThrottle()));
        luaSetVar("Engine_ManifoldPressure", std::to_string(engine->getManifoldPressure()));

        // get avg exhaust airflow
        double avg = 0;
        int i = 0;
        for (i = 0; i < engine->getExhaustSystemCount(); i++) {
            avg += engine->getExhaustSystem(i)->getFlow();
        }
        avg /= i;

        luaSetVar("Engine_ExhaustFlow", std::to_string(avg));

        avg = 0;
        i = 0;
        for (i = 0; i < engine->getIntakeCount(); i++) {
            avg += engine->getIntake(i)->m_flow;
        }
        avg /= i;

        luaSetVar("Engine_IntakeFlow", std::to_string(avg));

        double* ratios = getSimulator()->getTransmission()->m_gearRatios;
        luaSetVar("Engine_Gear1", std::to_string(ratios[0]));
        luaSetVar("Engine_Gear2", std::to_string(ratios[1]));
        luaSetVar("Engine_Gear3", std::to_string(ratios[2]));
        luaSetVar("Engine_Gear4", std::to_string(ratios[3]));
        luaSetVar("Engine_Gear5", std::to_string(ratios[4]));
        luaSetVar("Engine_Gear6", std::to_string(ratios[5]));

        luaSetVar("Simulator_FPS", std::to_string(m_engine.GetAverageFramerate()));
    }
    
    luaSetVar("Loader_Version", getModLoaderVersion());
    luaSetVar("Loader_Sim_Version", getBuildVersion());
    //free(engine);
}

void EngineSimApplication::luaGetEngineVars() {
    std::string result = "";
    Engine* engine = m_simulator.getEngine();

    result = luaGetVar("Engine_Throttle");
    double throt = std::stod(result);
    engine->setThrottle(throt);

    result = luaGetVar("Engine_ManifoldPressure");
    double press = std::stod(result);
    //for (int i = 0; engine->getIntakeCount(); i++) {
    //    //Simulator* sim = &m_simulator;
    //    //sim->getEngine()->getIntake(i)->addPress = press;
    //}
    //engine->press = press;
    //Logger::DebugLine("setting intake press: " + result);

    result = luaGetVar("Engine_IntakeFlow");
    double flow = std::stod(result);
    //engine->flow = flow;
    //Logger::DebugLine("setting intake flow: " + result);
    
    //double res[5] = {};
    //result = luaGetVar("Engine_Gear1");
    //res[0] = std::stod(result);
    //result = luaGetVar("Engine_Gear2");
    //res[1] = std::stod(result);
    //result = luaGetVar("Engine_Gear3");
    //res[2] = std::stod(result);
    //result = luaGetVar("Engine_Gear4");
    //res[3] = std::stod(result);
    //result = luaGetVar("Engine_Gear5");
    //res[4] = std::stod(result);
    //result = luaGetVar("Engine_Gear6");
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

/*
void EngineSimApplication::luaSetUiVar(std::string color)
{
    std::string resultR = "";
    std::string resultG = "";
    std::string resultB = "";
    double R = 0;
    double G = 0;
    double B = 0;

    resultR = luaGetVar("UI_" + color +"_R");
    resultG = luaGetVar("UI_" + color + "_G");
    resultB = luaGetVar("UI_" + color + "_B");
    R = std::stod(resultR);
    G = std::stod(resultG);
    B = std::stod(resultB);
    
    if (color == "pink") {
        SetPink(R, G, B);
    } else if (color == "green") {
        SetGreen(R, G, B);
    } else if (color == "yellow") {
        SetYellow(R, G, B);
    } else if (color == "red") {
        SetRed(R, G, B);
    } else if (color == "orange") {
        SetOrange(R, G, B);
    } else if (color == "blue") {
        SetBlue(R, G, B);
    }
}
*/

std::string EngineSimApplication::luaGetVar(std::string name) {
    const int len = name.length();
    char* nameChar = (char*)malloc(len + 1);
    strcpy(nameChar, name.c_str());

    lua_getglobal(L, nameChar);
    int top = lua_gettop(L);
    std::string str = lua_tostring(L, top);
    lua_pop(L, top);

    free(nameChar);

    return str;
}

void EngineSimApplication::luaSetVar(std::string name, std::string value) {
    const int len = name.length();
    char* nameChar = (char*)malloc(len + 1);
    strcpy(nameChar, name.c_str());

    const int len2 = value.length();
    char* valChar = (char*)malloc(len2 + 1);
    strcpy(valChar, value.c_str());

    lua_pushstring(L, valChar);

    lua_setglobal(L, nameChar);

    free(nameChar);
    free(valChar);
}

void EngineSimApplication::loadLua(std::string luaPath) {
    char buff[256];
    int error;
    L = luaL_newstate();
    luaL_openlibs(L);
    //luaL_dostring(L, "json = dofile('json.lua')");
    ap = this;

    Logger::DebugLine("===============================================================");
    Logger::DebugLine("===============================================================");
    Logger::DebugLine("=======================loader-engine===========================");
    Logger::DebugLine("==========================loading==============================");
    Logger::DebugLine("===============================================================");
    Logger::DebugLine("===============================================================");

    Logger::DebugLine("Setting up lua functions");
    lua_pushcclosure(L, luaTrace, 0);
    lua_setglobal(L, "trace");
    lua_pushcclosure(L, luaInfo, 0);
    lua_setglobal(L, "info");

    lua_pushcclosure(L, luaSetPink, 0);
    lua_setglobal(L, "setPink");
    lua_pushcclosure(L, luaSetGreen, 0);
    lua_setglobal(L, "setGreen");
    lua_pushcclosure(L, luaSetYellow, 0);
    lua_setglobal(L, "setYellow");
    lua_pushcclosure(L, luaSetRed, 0);
    lua_setglobal(L, "setRed");
    lua_pushcclosure(L, luaSetOrange, 0);
    lua_setglobal(L, "setOrange");
    lua_pushcclosure(L, luaSetBlue, 0);
    lua_setglobal(L, "setBlue");

    lua_pushcclosure(L, luaSetVolume, 0);
    lua_setglobal(L, "setVolume");
    lua_pushcclosure(L, luaSetFrequency, 0);
    lua_setglobal(L, "setFrequency");

    lua_pushcclosure(L, luaSetTorqueUnit, 0);
    lua_setglobal(L, "setTorqueUnit");
    lua_pushcclosure(L, luaSetSpeedUnit, 0);
    lua_setglobal(L, "setSpeedUnit");
    lua_pushcclosure(L, luaSetAirflowUnit, 0);
    lua_setglobal(L, "setAirflowUnit");
    lua_pushcclosure(L, luaSetPressureUnit, 0);
    lua_setglobal(L, "setPressureUnit");

    Logger::DebugLine("Setting up lua handlers");
    lua_pushcclosure(L, addInputHandler, 0);
    lua_setglobal(L, "addProcessHandler");
    lua_pushcclosure(L, addStartHandler, 0);
    lua_setglobal(L, "addStartHandler");

    Logger::DebugLine("Loading files...");


    for (const auto& entry : fs::directory_iterator(luaPath)) {
        std::string path = entry.path().string();
        if (path != luaPath + "\\preConfig.lua" && path != luaPath + "\\config.lua")
        {
            Logger::DebugLine("Loading file: " + path);
            const int len = path.length();
            char* pathChar = (char*)malloc(len + 1);
            strcpy(pathChar, path.c_str());
            //luaL_loadfile(L, pathChar);
            luaL_dofile(L, pathChar);
            s_modAmount++;
            free(pathChar);
        }
    }

    Logger::DebugLine("Loading preConfig...");
    if (fs::exists(luaPath + "\\preConfig.lua")) {
        const int len = (luaPath + "/preConfig.lua").length();
        char* pathChar = (char*)malloc(len + 1);
        strcpy(pathChar, (luaPath + "/preConfig.lua").c_str());

        // prepare for compiling file
        //luaSetupEngineVars(true);

        luaL_dofile(L, pathChar);

        // Get results
        //luaGetUiVars();

        Logger::DebugLine("PreConfig Loaded");
        free(pathChar);
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
        const int len = (luaPath + "/config.lua").length();
        char* pathChar = (char*)malloc(len + 1);
        strcpy(pathChar, (luaPath + "/config.lua").c_str());

        // prepare for compiling file
        //luaSetupEngineVars(true);

        luaL_dofile(L, pathChar);

        // Get results
        //luaGetUiVars();

        Logger::DebugLine("Config Loaded");
        free(pathChar);
    }
    else {
        Logger::DebugLine("Config Not loaded: file not found");
    }
}

void EngineSimApplication::luaFail(std::string error) {
    Logger::DebugLine(error);
}

void EngineSimApplication::unloadLua() {
    lua_close(L);
}
