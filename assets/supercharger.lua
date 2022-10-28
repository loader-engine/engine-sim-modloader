-- EXAMPLE GLOBAL VARIABLES:
ModName = "Supercharger mod"
ModDescription = "Adds a supercharger to ES"
ModControls = "U - disable supercharger (hold)"
ModVersion = "0.0.1"

supercharger_spool = 0

supercharger_to_press = 5
supercharger_press_to_flow = 5000
supercharger_rpm_to_flow = 1000

function OnProcess(dt)
	
	-- this function is executed on EngineSimApplication::process()
	-- available vars and functions are listed in the documentation

	press = 40 * (1 - es.engine.Throttle)
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
