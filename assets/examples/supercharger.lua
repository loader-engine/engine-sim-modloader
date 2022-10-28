-- EXAMPLE GLOBAL VARIABLES:
ModName = "Supercharger mod"
ModDescription = "Adds a supercharger to ES"
ModControls = "U - disable supercharger (hold)"
ModVersion = "0.0.1"

es.loader.import("../assets/config/normalSupercharger.lua")

function OnProcess(dt)
	
	-- this function is executed on EngineSimApplication::process()
	-- available vars and functions are listed in the documentation

	flow = es.engine.RPM / supercharger_rpm_to_flow

	supercharger_spool = supercharger_spool + flow

	if supercharger_spool > supercharger_max then
		supercharger_spool = supercharger_max
	else
		supercharger_spool = supercharger_spool + supercharger_down
	end

	if supercharger_spool < 0.5 then
		supercharger_spool = -0.5
	end

es.trace(supercharger_spool)

	press = supercharger_spool / supercharger_to_press
	flow = press * supercharger_press_to_flow

	if INPUT_U == "false" then
		es.engine.SetManifoldPressure(press)
		es.engine.SetIntakeFlow(flow)

		
		es.trace(press)
	end

end

function OnStart()
	
	-- this function is executed on EngineSimApplication::initialize()
	-- before anything executes
	-- there is no input here!

end

addStartHandler(OnStart)
addProcessHandler(OnProcess)

message = string.format("Loaded Supercharger Mod %s", ModVersion)
es.trace(message)

message = string.format("Controls: %s", ModControls)
es.trace(message)

es.engine.setIgnition(false, 1500)
es.engine.setInjection(false, 1500)
