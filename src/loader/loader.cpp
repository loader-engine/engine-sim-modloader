
#include "../../include/loader/luad.h"
#include "../../include/engine_sim_application.h"
#include "../../include/utilities.h"
#include "../../include/lua/lua.hpp"

namespace fs = std::filesystem;

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

        if (lua_pcall(luad::data::L, 1, 0, 0) != LUA_OK) {
            const char* msg = lua_tostring(luad::data::L, -1);
            luaErr(msg);
        }
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

        if (lua_pcall(luad::data::L, 0, 0, 0) != LUA_OK) {
            const char* msg = lua_tostring(luad::data::L, -1);
            luaErr(msg);
        }
    }
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
        
        if (lua_pcall(luad::data::L, 0, 0, 0) != LUA_OK) {
            const char* msg = lua_tostring(luad::data::L, -1);
            luaErr(msg);
        }
    }
}

void EngineSimApplication::luaErr(std::string message) {
    luad::utils::luaError(message);
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
        Transmission* transmission = m_simulator.getTransmission();
        Vehicle* vehicle = m_simulator.getVehicle();
        if (engine != nullptr) {
            luad::utils::luaSetVar("Engine_Name", engine->getName());

            luad::utils::luaSetVar("Engine_RPM", std::to_string(engine->getRpm()));
            luad::utils::luaSetVar("Engine_Speed", std::to_string(vehicle->getSpeed()));
            luad::utils::luaSetVar("Engine_Redline", std::to_string(units::toRpm(engine->getRedline())));
            luad::utils::luaSetVar("Engine_Gear", std::to_string(transmission->getGear()));
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

            luad::utils::luaSetVar("Simulator_FPS", std::to_string(m_engine.GetAverageFramerate()));
        }
    }
    
    if (m_loadSimulationCluster != nullptr) {
        luad::utils::luaSetVar("Dyno_Torque", std::to_string(m_loadSimulationCluster->m_filteredTorque));
        luad::utils::luaSetVar("Dyno_Power", std::to_string(m_loadSimulationCluster->m_filteredHorsepower));
    }

    luad::utils::luaSetVar("Loader_Version", getModLoaderVersion());
    luad::utils::luaSetVar("Loader_Sim_Version", getBuildVersion());
}

void EngineSimApplication::luaGetEngineVars() {
    std::string result = "";
    Engine* engine = m_simulator.getEngine();

    if (engine != nullptr) {
        result = luad::utils::luaGetVar("Engine_Throttle");
        double throt = std::stod(result);
        engine->setThrottle(throt);

        result = luad::utils::luaGetVar("Engine_ManifoldPressure");
        double press = std::stod(result);

        result = luad::utils::luaGetVar("Engine_IntakeFlow");
        double flow = std::stod(result);

        engine->UpdateShit();
    }
}

void EngineSimApplication::reloadLua(std::string luaPath) {
    luad::data::reloading = true;

    for (int i = 0; i < 100; i++) {
        process_handlers[i] = 0;
        tick_handlers[i] = 0;
        start_handlers[i] = 0;
    }

    numProcessHandlers = 0;
    numTickHandlers = 0;
    numStartHandlers = 0;
    
    luad::data::reinit();
    loadLua(luaPath, false);

    luad::data::reloading = false;
}

void EngineSimApplication::loadLua(std::string luaPath, bool first) {
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

    luad::utils::luaPushFunction("CsetModel", luad::functions::luaSetModel);
    luad::utils::luaPushFunction("CsetTexture", luad::functions::luaSetTexture);
    luad::utils::luaPushFunction("CloadTexture", luad::functions::luaLoadTexture);

    luad::utils::luaPushFunction("CsetIgnition", luad::functions::luaSetIgnition);
    luad::utils::luaPushFunction("CsetInjection", luad::functions::luaSetInjection);

    luad::utils::luaPushFunction("CsetCrankWeight", luad::functions::luaSetCrankWeight);
    luad::utils::luaPushFunction("CsetFlywheelWeight", luad::functions::luaSetFlywheelWeight);
    luad::utils::luaPushFunction("CsetPistonWeight", luad::functions::luaSetPistonWeight);
    luad::utils::luaPushFunction("CsetConrodWeight", luad::functions::luaSetConrodWeight);

    luad::utils::luaPushFunction("CsetGlobalInput", luad::functions::luaSetGlobalInput);

    luad::utils::luaPushFunction("CsetThrottle", luad::functions::luaSetThrottle);
    luad::utils::luaPushFunction("CsetManifoldPressure", luad::functions::luaSetManifoldPressure);
    luad::utils::luaPushFunction("CsetIntakeFlow", luad::functions::luaSetIntakeFlow);
    
    luad::utils::luaPushFunction("Cimport", luad::functions::luaImport);

    // IO
    luad::utils::luaPushFunction("CinitDNet", luad::functions::luaInitDNet);
    luad::utils::luaPushFunction("CsendDNet", luad::functions::luaSendDNet);

    // JSON
    luad::utils::luaPushFunction("CjsonNew", luad::functions::luaJSONNew);
    luad::utils::luaPushFunction("CjsonAddString", luad::functions::luaJSONAddString);
    luad::utils::luaPushFunction("CjsonAddInt", luad::functions::luaJSONAddInt);
    luad::utils::luaPushFunction("CjsonAddNumber", luad::functions::luaJSONAddNumber);
    luad::utils::luaPushFunction("CjsonGetString", luad::functions::luaJSONGetString);

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
            if (luaL_dofile(luad::data::L, path.c_str()) != LUA_OK) {
                const char* msg = lua_tostring(luad::data::L, -1);
                luaErr(msg);
            }
            s_modAmount++;
        }
    }

    Logger::DebugLine("Loading preConfig...");
    if (fs::exists(luaPath + "\\preConfig.lua")) {
        if (luaL_dofile(luad::data::L, (luaPath + "/preConfig.lua").c_str()) != LUA_OK) {
            const char* msg = lua_tostring(luad::data::L, -1);
            luaErr(msg);
        }

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
        if (luaL_dofile(luad::data::L, (luaPath + "/config.lua").c_str()) != LUA_OK) {
            const char* msg = lua_tostring(luad::data::L, -1);
            luaErr(msg);
        }

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
