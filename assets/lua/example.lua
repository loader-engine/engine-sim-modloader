-- EXAMPLE GLOBAL VARIABLES:
ModName = "Example mod"
ModDescription = "Example mod description"
ModVersion = "0.0.1"

time = 0

function OnProcess(dt)
	
	-- this function is executed on EngineSimApplication::process()
	-- avaiable vars and functions are listed in the documentation

end

function OnTick(dt)

	-- processes audio mostly

end

function OnStart()
	
	-- this function is executed on EngineSimApplication::initialize()
	-- before anything executes
	-- there is no input here!

end

addStartHandler(OnStart)
addProcessHandler(OnProcess)
addTickHandler(OnTick)

message = string.format("Loaded Example Mod %s", ModVersion)
es.trace(message)
es.setModel("piston", "HemiPiston")

-- Please don't do this.
-- info("Loaded mod")
