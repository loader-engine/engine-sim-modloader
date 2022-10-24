
#include "../../include/loader/luad.h"
#include "../../include/engine_sim_application.h"
#include "../../include/utilities.h"
#include "../../include/lua/lua.hpp"

EngineSimApplication* luad::data::app = nullptr;
lua_State* luad::data::L = nullptr;
bool luad::data::reloading = false;
std::map<std::string, int> luad::data::materialMap = {};

std::string luad::data::pistonModelName = "Piston";
std::string luad::data::headModelName = "CylinderHead";
std::string luad::data::exhValveModelName = "Valve";
std::string luad::data::intValveModelName = "Valve";
std::string luad::data::crankshaftModelName = "Crankshaft";
std::string luad::data::crankshaftSnoutModelName = "CrankSnout";
std::string luad::data::crankshaftSnoutThreadsModelName = "CrankSnoutThreads";
std::string luad::data::connectingRodModelName = "ConnectingRod";

/*
std::string luad::data::pistonTextureName = "PistonTexture";
std::string luad::data::headTextureName = "CylinderHeadTexture";
std::string luad::data::exhValveTextureName = "ValveTexture";
std::string luad::data::intValveTextureName = "ValveTexture";
std::string luad::data::crankshaftTextureName = "CrankshaftTexture";
std::string luad::data::crankshaftSnoutTextureName = "CrankSnoutTexture";
std::string luad::data::crankshaftSnoutThreadsTextureName = "CrankSnoutThreadsTexture";
std::string luad::data::connectingRodTextureName = "ConnectingRodTexture";
*/

std::string luad::data::pistonTextureName = "None";
std::string luad::data::headTextureName = "None";
std::string luad::data::exhValveTextureName = "None";
std::string luad::data::intValveTextureName = "None";
std::string luad::data::crankshaftTextureName = "None";
std::string luad::data::crankshaftSnoutTextureName = "None";
std::string luad::data::crankshaftSnoutThreadsTextureName = "None";
std::string luad::data::connectingRodTextureName = "None";

djson::json luad::data::json = djson::json();
std::string luad::data::jsonStr = "";

luad::data::data() {

}

void luad::data::init(EngineSimApplication* engineSimApplication) {
	app = engineSimApplication;

	L = luaL_newstate();
	luaL_openlibs(L);
	//luaL_dostring(L, "json = dofile('json.lua')");
}

void luad::data::reinit() {
	lua_close(L);
	
	// reinit
	L = luaL_newstate();
	luaL_openlibs(L);
}
