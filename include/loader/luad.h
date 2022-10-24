#pragma once

#include "../engine_sim_application.h"
#include "../utilities.h"
#include "../lua/lua.hpp"
#include "../ddevlib/djson/djson.hpp"
#include <map>

namespace luad {
	
	class data {
	public:
		data();
	
	public:

		static void init(EngineSimApplication* engineSimApplication);
		static void reinit();

		static EngineSimApplication* app;
		static lua_State* L;
		static bool reloading;

		static djson::json json;
		static std::string jsonStr;

		static std::string pistonModelName;
		static std::string headModelName;
		static std::string exhValveModelName;
		static std::string intValveModelName;
		static std::string crankshaftModelName;
		static std::string crankshaftSnoutModelName;
		static std::string crankshaftSnoutThreadsModelName;
		static std::string connectingRodModelName;

		static std::string pistonTextureName;
		static std::string headTextureName;
		static std::string exhValveTextureName;
		static std::string intValveTextureName;
		static std::string crankshaftTextureName;
		static std::string crankshaftSnoutTextureName;
		static std::string crankshaftSnoutThreadsTextureName;
		static std::string connectingRodTextureName;

		static std::map<std::string, int> materialMap;

	};

	class functions {
	public:

		functions();

		static int endDNet();

		// template:
		// static int lua(lua_State* lua);

	public:
		static int luaTrace(lua_State* lua);
		static int luaInfo(lua_State* lua);

		static int luaSetModel(lua_State* lua);
		static int luaSetTexture(lua_State* lua);
		static int luaLoadTexture(lua_State* lua);

		static int luaAddSynth(lua_State* lua);

		static int luaSetGlobalInput(lua_State* lua);

		// IO
		static int luaInitDNet(lua_State* lua);
		static int luaSendDNet(lua_State* lua);

		// JSON
		static int luaJSONNew(lua_State* lua);
		static int luaJSONGetString(lua_State* lua);
		static int luaJSONAddString(lua_State* lua);
		static int luaJSONAddInt(lua_State* lua);
		static int luaJSONAddNumber(lua_State* lua);

		// Engine
		static int luaSetAntilag(lua_State* lua);
		static int luaSetMixture(lua_State* lua);
		static int luaSetIgnition(lua_State* lua);
		static int luaSetInjection(lua_State* lua);

		static int luaSetThrottle(lua_State* lua);
		static int luaSetManifoldPressure(lua_State* lua);
		static int luaSetIntakeFlow(lua_State* lua);

		static int luaImport(lua_State* lua);

		static int luaSetCrankWeight(lua_State* lua);
		static int luaSetFlywheelWeight(lua_State* lua);
		static int luaSetPistonWeight(lua_State* lua);
		static int luaSetConrodWeight(lua_State* lua);
		
		// Useless
		static int luaSetGear(lua_State* lua);
		
		static int luaSetBlue(lua_State* lua);
		static int luaSetGreen(lua_State* lua);
		static int luaSetYellow(lua_State* lua);
		static int luaSetPink(lua_State* lua);
		static int luaSetRed(lua_State* lua);
		static int luaSetOrange(lua_State* lua);

		static int luaSetAirflowUnit(lua_State* lua);
		static int luaSetPressureUnit(lua_State* lua);
		static int luaSetSpeedUnit(lua_State* lua);
		static int luaSetTorqueUnit(lua_State* lua);
		static int luaSetFrequency(lua_State* lua);
		static int luaSetVolume(lua_State* lua);

	};

	enum class partType {
		unknown,

		piston,

		head,
		exhaustValve,
		intakeValve,

		crankshaft,
		crankSnout,
		crankSnoutThreads,

		connectingRod
	};

	class utils {
	public:

		utils();

	public:
		
		static std::string luaGetVar(std::string name);
		static void luaSetVar(std::string name, std::string value);

		static void luaPushFunction(std::string name, lua_CFunction function);

		static luad::partType decodePart(std::string part);
		static dbasic::Material* getMaterialByName(std::string name);

		static void luaError(std::string message);

	};

}
