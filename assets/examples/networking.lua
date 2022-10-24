-- EXAMPLE GLOBAL VARIABLES:
ModName = "Networking mod"
ModDescription = "Adds networking to ES"
ModVersion = "0.0.1"

networking_set_input = false

function OnProcess(dt)
	
	-- this function is executed on EngineSimApplication::process()
	-- available vars and functions are listed in the documentation

	es.loader.json.new()

	es.loader.json.addString("loader_version", es.loader.Version)
	es.loader.json.addString("version", es.loader.SimVersion)
	es.loader.json.addString("engine_name", es.engine.Name)

	es.loader.json.addString("torque", es.engine.dyno.Torque)
	es.loader.json.addString("power", es.engine.dyno.Power)
	
	es.loader.json.addString("rpm", es.engine.RPM)
	es.loader.json.addString("speed", es.engine.Speed)
	es.loader.json.addString("redline", es.engine.Redline)
	es.loader.json.addString("gear", es.engine.Gear)

	es.loader.json.addString("afr", es.engine.AFR)
	es.loader.json.addString("press", es.engine.ManifoldPressure)
	es.loader.json.addString("flow", es.engine.IntakeFlow)
	es.loader.json.addString("throttle", es.engine.Throttle)

	es.loader.sendDNet(es.loader.json.getString())

	if networking_set_input == false then
		es.loader.setGlobalInput(true)
		networking_set_input = true		
	end

end

function OnStart()
	
	-- this function is executed on EngineSimApplication::initialize()
	-- before anything executes
	-- there is no input here!

end

addStartHandler(OnStart)
addProcessHandler(OnProcess)

message = string.format("Loaded Networking Mod %s", ModVersion)
es.trace(message)
es.loader.initDNet()
