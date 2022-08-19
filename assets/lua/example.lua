-- EXAMPLE GLOBAL VARIABLES:
ModName = "Example mod"
ModDescription = "Example mod decription"
ModVersion = "0.0.1"

function OnProcess(dt)
	
	-- this function is executed on EngineSimApplication::process()
	-- avaiable vars and functions are listed in the documentation

end

function OnStart()
	
	-- this function is executed on EngineSimApplication::initialize()
	-- before anything executes
	-- there is no input here!

end

addStartHandler(OnStart)
addProcessHandler(OnProcess)
message = string.format("Loaded Example Mod %s", ModVersion)
trace(message)

--info("Loaded mod")
