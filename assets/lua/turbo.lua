-- EXAMPLE GLOBAL VARIABLES:
ModName = "Turbo mod"
ModDescription = "Adds a turbocharger to ES"
ModControls = "L - Antilag, U - disable turbo (hold)"
ModVersion = "0.0.2"

es.loader.import("../assets/config/reallysmolTurbo.lua")

function OnProcess(dt)
	
	-- this function is executed on EngineSimApplication::process()
	-- available vars and functions are listed in the documentation

	flow = es.engine.ExhaustFlow * turbo_flow_mult

	flow = flow * (es.engine.RPM / turbo_rpm_to_flow)

	if INPUT_L == "true" then
		flow = flow * turbo_antilag_flow
	end

	turbo_spool = turbo_spool + flow

	if turbo_spool < turbo_max then
		turbo_spool = turbo_max
	else
		turbo_spool = turbo_spool + turbo_down
	end

	if turbo_spool > 0.5 then
		turbo_spool = 0.5
	end

	press = -turbo_spool / turbo_to_press
	flow = press * turbo_press_to_flow

	if INPUT_U == "false" then
		es.engine.SetManifoldPressure(press)
		es.engine.SetIntakeFlow(flow)

		--es.trace(string.format("PRESS : %s", press))
		--es.trace(string.format("FLOW  : %s", flow))
	end

	--es.trace(-turbo_spool)

end

function OnStart()
	
	-- this function is executed on EngineSimApplication::initialize()
	-- before anything executes
	-- there is no input here!

end

addStartHandler(OnStart)
addProcessHandler(OnProcess)

message = string.format("Loaded Turbo Mod %s", ModVersion)
es.trace(message)

message = string.format("Controls: %s", ModControls)
es.trace(message)

es.engine.setIgnition(false, 1500)
es.engine.setInjection(false, 1500)

-- Please don't do this.
-- info("Loaded mod")
