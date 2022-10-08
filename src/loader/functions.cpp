
#include "../../include/loader/luad.h"
#include "../../include/engine_sim_application.h"
#include "../../include/utilities.h"
#include "../../include/lua/lua.hpp"
#include "../../include/ddevlib/dnet/dnet.hpp"

luad::functions::functions() {

}

int luad::functions::luaSetCrankWeight(lua_State* lua) {
    assert(lua_isnumber(lua, 1));

    const double value = (double)lua_tonumber(lua, 1);
    for (int i = 0; i < luad::data::app->m_iceEngine->getCrankshaftCount(); i++) {
        luad::data::app->m_iceEngine->getCrankshaft(i)->m_m = value;
    }

    return 0;
}

int luad::functions::luaInitDNet(lua_State* lua) {
    int result = dnet::net::init();
    return result;
}

int luad::functions::endDNet() {
    int result = dnet::net::end();
    return result;
}

int luad::functions::luaSetFlywheelWeight(lua_State* lua) {
    assert(lua_isnumber(lua, 1));

    const double value = (double)lua_tonumber(lua, 1);
    for (int i = 0; i < luad::data::app->m_iceEngine->getCrankshaftCount(); i++) {
        luad::data::app->m_iceEngine->getCrankshaft(i)->m_I = (1 / 2.0) * (value * units::kg) * (0.2 * units::m) * (0.2 * units::m);
        luad::data::app->m_iceEngine->getCrankshaft(i)->m_flywheelMass = (value * units::kg);
        Logger::DebugLine(std::to_string((value * units::kg)));
        Logger::DebugLine(std::to_string((1 / 2.0) * (value * units::kg) * (0.2 * units::m) * (0.2 * units::m)));
    }

    return 0;
}

int luad::functions::luaSetPistonWeight(lua_State* lua) {
    assert(lua_isnumber(lua, 1));

    const double value = (double)lua_tonumber(lua, 1);
    for (int i = 0; i < luad::data::app->m_iceEngine->getCylinderCount(); i++) {
            luad::data::app->m_iceEngine->getPiston(i)->m_mass = value;
    }

    return 0;
}

int luad::functions::luaSetConrodWeight(lua_State* lua) {
    assert(lua_isnumber(lua, 1));

    const double value = (double)lua_tonumber(lua, 1);
    for (int i = 0; i < luad::data::app->m_iceEngine->getCylinderCount(); i++) {
        luad::data::app->m_iceEngine->getConnectingRod(i)->m_m = value;
    }

    return 0;
}

int luad::functions::luaSetModel(lua_State* lua) {
    assert(lua_isstring(lua, 1));
    assert(lua_isstring(lua, 2));

    const char* part = lua_tostring(lua, 1);
    const char* modelName = lua_tostring(lua, 2);

    std::string partStr(part);
    std::string modelNameStr(modelName);

    // make partStr lowercase
    for (int i = 0; i < partStr.length(); ++i)
        partStr[i] = tolower(partStr[i]);

    // set model for part
    Logger::DebugLine("Setting part " + partStr + " model to: " + modelNameStr);

    luad::partType type = luad::utils::decodePart(partStr);

    switch (type)
    {
    case luad::partType::unknown:
        Logger::DebugLine("Unknown part.");
        return 1;
        break;
    case luad::partType::piston:
        luad::data::pistonModelName = modelNameStr;
        break;
    case luad::partType::head:
        luad::data::headModelName = modelNameStr;
        break;
    case luad::partType::exhaustValve:
        luad::data::exhValveModelName = modelNameStr;
        break;
    case luad::partType::intakeValve:
        luad::data::intValveModelName = modelNameStr;
        break;
    case luad::partType::crankshaft:
        luad::data::crankshaftModelName = modelNameStr;
        break;
    case luad::partType::crankSnout:
        luad::data::crankshaftSnoutModelName = modelNameStr;
        break;
    case luad::partType::crankSnoutThreads:
        luad::data::crankshaftSnoutThreadsModelName = modelNameStr;
        break;
    case luad::partType::connectingRod:
        luad::data::connectingRodModelName = modelNameStr;
        break;
    default:
        Logger::DebugLine("Default case fired, unknown error happened.");
        return 1;
        break;
    }

    return 0;
}

int luad::functions::luaSetTexture(lua_State* lua) {
    assert(lua_isstring(lua, 1));
    assert(lua_isstring(lua, 2));

    const char* part = lua_tostring(lua, 1);
    const char* textureName = lua_tostring(lua, 2);

    std::string partStr(part);
    std::string textureNameStr(textureName);

    // make partStr lowercase
    for (int i = 0; i < partStr.length(); ++i)
        partStr[i] = tolower(partStr[i]);

    // set model for part
    Logger::DebugLine("Setting part " + partStr + " texture to: " + textureNameStr);

    luad::partType type = luad::utils::decodePart(partStr);

    switch (type)
    {
    case luad::partType::unknown:
        Logger::DebugLine("Unknown part.");
        return 1;
        break;
    case luad::partType::piston:
        luad::data::pistonTextureName = textureNameStr;
        break;
    case luad::partType::head:
        luad::data::headTextureName = textureNameStr;
        break;
    case luad::partType::exhaustValve:
        luad::data::exhValveTextureName = textureNameStr;
        break;
    case luad::partType::intakeValve:
        luad::data::intValveTextureName = textureNameStr;
        break;
    case luad::partType::crankshaft:
        luad::data::crankshaftTextureName = textureNameStr;
        break;
    case luad::partType::crankSnout:
        luad::data::crankshaftSnoutTextureName = textureNameStr;
        break;
    case luad::partType::crankSnoutThreads:
        luad::data::crankshaftSnoutThreadsTextureName = textureNameStr;
        break;
    case luad::partType::connectingRod:
        luad::data::connectingRodTextureName = textureNameStr;
        break;
    default:
        Logger::DebugLine("Default case fired, unknown error happened.");
        return 1;
        break;
    }

    return 0;
}


int luad::functions::luaLoadTexture(lua_State* lua) {
    assert(lua_isstring(lua, 1));

    const char* textureName = lua_tostring(lua, 1);

    std::string textureNameStr(textureName);

    Logger::DebugLine("Loading texture " + textureNameStr + ".png");

    std::string texturePath = "../assets/textures/" + textureNameStr;
    if(luad::data::app->m_assetManager.GetTexture(textureName) != nullptr) {
        luad::data::app->m_assetManager.LoadTexture(texturePath.c_str(), textureName);
        dbasic::Material* mat = luad::data::app->m_assetManager.NewMaterial();
        mat->SetName(textureName);
        mat->SetDiffuseMap(luad::data::app->m_assetManager.GetTexture(texturePath.c_str())->GetTexture());
    
        luad::data::materialMap.insert({ textureName, mat->GetIndex() });
    }
    else {
        if(!luad::data::reloading)
            Logger::DebugLine("Texture already loaded!");
        return 1;
    }

    return 0;
}

int luad::functions::luaTrace(lua_State* lua)
{
    assert(lua_isstring(lua, 1));

    const char* msg = lua_tostring(lua, 1);
    std::string str(msg);

    // debug output
    Logger::DebugLine("script: " + str);

    return 0;
}

int luad::functions::luaSetPink(lua_State* lua) {
    assert(lua_isnumber(lua, 1));
    assert(lua_isnumber(lua, 2));
    assert(lua_isnumber(lua, 3));

    const int r = (int)lua_tonumber(lua, 1);
    const int g = (int)lua_tonumber(lua, 2);
    const int b = (int)lua_tonumber(lua, 3);

    EngineSimApplication::instance->SetPink(r, g, b);

    return 0;
}
int luad::functions::luaSetGreen(lua_State* lua) {
    assert(lua_isnumber(lua, 1));
    assert(lua_isnumber(lua, 2));
    assert(lua_isnumber(lua, 3));

    const int r = (int)lua_tonumber(lua, 1);
    const int g = (int)lua_tonumber(lua, 2);
    const int b = (int)lua_tonumber(lua, 3);

    EngineSimApplication::instance->SetGreen(r, g, b);

    return 0;
}
int luad::functions::luaSetYellow(lua_State* lua) {
    assert(lua_isnumber(lua, 1));
    assert(lua_isnumber(lua, 2));
    assert(lua_isnumber(lua, 3));

    const int r = (int)lua_tonumber(lua, 1);
    const int g = (int)lua_tonumber(lua, 2);
    const int b = (int)lua_tonumber(lua, 3);

    EngineSimApplication::instance->SetYellow(r, g, b);

    return 0;
}
int luad::functions::luaSetRed(lua_State* lua) {
    assert(lua_isnumber(lua, 1));
    assert(lua_isnumber(lua, 2));
    assert(lua_isnumber(lua, 3));

    const int r = (int)lua_tonumber(lua, 1);
    const int g = (int)lua_tonumber(lua, 2);
    const int b = (int)lua_tonumber(lua, 3);

    EngineSimApplication::instance->SetRed(r, g, b);

    return 0;
}
int luad::functions::luaSetOrange(lua_State* lua) {
    assert(lua_isnumber(lua, 1));
    assert(lua_isnumber(lua, 2));
    assert(lua_isnumber(lua, 3));

    const int r = (int)lua_tonumber(lua, 1);
    const int g = (int)lua_tonumber(lua, 2);
    const int b = (int)lua_tonumber(lua, 3);

    EngineSimApplication::instance->SetOrange(r, g, b);

    return 0;
}
int luad::functions::luaSetBlue(lua_State* lua) {
    assert(lua_isnumber(lua, 1));
    assert(lua_isnumber(lua, 2));
    assert(lua_isnumber(lua, 3));

    const int r = (int)lua_tonumber(lua, 1);
    const int g = (int)lua_tonumber(lua, 2);
    const int b = (int)lua_tonumber(lua, 3);

    EngineSimApplication::instance->SetBlue(r, g, b);

    return 0;
}

int luad::functions::luaSetVolume(lua_State* lua) {
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

int luad::functions::luaSetFrequency(lua_State* lua) {
    assert(lua_isnumber(lua, 1));

    int freq = (int)lua_tonumber(lua, 1);
    freq = clamp(freq, 400.0, 400000.0);

    EngineSimApplication::instance->m_simulator.setSimulationFrequency(freq);

    return 0;
}

int luad::functions::luaSetAntilag(lua_State* lua) {
    assert(lua_isboolean(lua, 1));
    assert(lua_isboolean(lua, 2));

    int set = lua_toboolean(lua, 1);
    int set2 = lua_toboolean(lua, 2);

    EngineSimApplication::instance->antilag = set == 1 ? true : false;
    EngineSimApplication::instance->often = set2 == 1 ? true : false;

    return 0;
}

int luad::functions::luaSetMixture(lua_State* lua) {
    assert(lua_isboolean(lua, 1));

    int set = lua_toboolean(lua, 1);

    for (int i = 0; i < EngineSimApplication::instance->m_simulator.getEngine()->getIntakeCount(); i++)
        EngineSimApplication::instance->m_simulator.getEngine()->getIntake(i)->rich = set;

    return 0;
}

int luad::functions::luaSetGear(lua_State* lua) {
    assert(lua_isnumber(lua, 1));
    assert(lua_isnumber(lua, 2));

    int index = (int)lua_tonumber(lua, 1);
    double ratio = (double)lua_tonumber(lua, 2);

    EngineSimApplication::instance->ratios[index] = ratio;

    return 0;
}

int luad::functions::luaSetTorqueUnit(lua_State* lua) {
    assert(lua_isstring(lua, 1));

    const char* type = lua_tostring(lua, 1);
    std::string str(type);

    EngineSimApplication::instance->UNIT_TYPE_TORQUE = str;
    Logger::DebugLine("Set torque unit to: " + str);

    return 0;
}

int luad::functions::luaSetSpeedUnit(lua_State* lua) {
    assert(lua_isstring(lua, 1));

    const char* type = lua_tostring(lua, 1);
    std::string str(type);

    EngineSimApplication::instance->UNIT_TYPE_SPEED = str;
    Logger::DebugLine("Set speed unit to: " + str);

    return 0;
}

int luad::functions::luaSetAirflowUnit(lua_State* lua) {
    assert(lua_isstring(lua, 1));

    const char* type = lua_tostring(lua, 1);
    std::string str(type);

    EngineSimApplication::instance->UNIT_TYPE_AIRFLOW = str;
    Logger::DebugLine("Set airflow unit to: " + str);

    return 0;
}

int luad::functions::luaSetPressureUnit(lua_State* lua) {
    assert(lua_isstring(lua, 1));

    const char* type = lua_tostring(lua, 1);
    std::string str(type);

    EngineSimApplication::instance->UNIT_TYPE_PRESSURE = str;
    Logger::DebugLine("Set pressure unit to: " + str);

    return 0;
}

int luad::functions::luaInfo(lua_State* lua)
{
    assert(lua_isstring(lua, 1));

    const char* msg = lua_tostring(lua, 1);
    std::string str(msg);

    // debug output
    luad::data::app->m_infoCluster->setLogMessage(msg);

    return 0;
}

int luad::functions::luaAddSynth(lua_State* lua) {
    assert(lua_isnumber(lua, 1));

    double value = (double)lua_tonumber(lua, 1);

    EngineSimApplication::instance->m_simulator.getSynthesizer()->writeInput(&value);
    //Logger::DebugLine(std::to_string(value));

    return 0;
}
