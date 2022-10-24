
#include "../../include/loader/luad.h"
#include "../../include/engine_sim_application.h"
#include "../../include/utilities.h"
#include "../../include/lua/lua.hpp"

luad::utils::utils() {

}

std::string luad::utils::luaGetVar(std::string name) {
    lua_getglobal(luad::data::L, name.c_str());
    int top = lua_gettop(luad::data::L);
    std::string str = lua_tostring(luad::data::L, top);
    lua_pop(luad::data::L, top);

    return str;
}

void luad::utils::luaSetVar(std::string name, std::string value) {
    lua_pushstring(luad::data::L, value.c_str());

    lua_setglobal(luad::data::L, name.c_str());
}

void luad::utils::luaPushFunction(std::string name, lua_CFunction function) {
    lua_pushcclosure(luad::data::L, function, 0);
    lua_setglobal(luad::data::L, name.c_str());
}

luad::partType luad::utils::decodePart(std::string part) {

    if (part == "piston") {
        return luad::partType::piston;
    }
    else if (part == "head") {
        return luad::partType::head;
    }
    else if (part == "cylinderhead") {
        return luad::partType::head;
    }
    else if (part == "exhaustValve") {
        return luad::partType::exhaustValve;
    }
    else if (part == "intakeValve") {
        return luad::partType::intakeValve;
    }
    else if (part == "crank") {
        return luad::partType::crankshaft;
    }
    else if (part == "crankshaft") {
        return luad::partType::crankshaft;
    }
    else if (part == "cranksnout") {
        return luad::partType::crankSnout;
    }
    else if (part == "crankshaftsnout") {
        return luad::partType::crankSnout;
    }
    else if (part == "cranksnoutthreads") {
        return luad::partType::crankSnoutThreads;
    }
    else if (part == "crankshaftsnoutthreads") {
        return luad::partType::crankSnoutThreads;
    }
    else if (part == "conrod") {
        return luad::partType::connectingRod;
    }
    else if (part == "connectingrod") {
        return luad::partType::connectingRod;
    }
    else {
        return luad::partType::unknown;
    }
}

dbasic::Material* luad::utils::getMaterialByName(std::string name) {
    for (std::pair<std::string, int> var : luad::data::materialMap) {
        dbasic::Material* mat = luad::data::app->getAssetManager()->GetMaterial(var.second);
        
        if (mat->GetName() == name) {
            return mat;
        }
    }

    return nullptr;
}

void luad::utils::luaError(std::string message) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf("ERROR: %s\n", message.c_str());
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
