-- EXAMPLE GLOBAL VARIABLES:
ModName = "Example mod"
ModDescription = "Example mod decription"
ModVersion = "0.0.1"

time = 0

function OnProcess(dt)
	
	-- this function is executed on EngineSimApplication::process()
	-- avaiable vars and functions are listed in the documentation
	
	
	-- :) should work

end

function OnTick(dt)

	-- processes audio mostly

	delta = dt * 10
	time = time + delta

	value = math.sin(time) * 100000;
	value = value * Engine_Throttle;

	synthAdd(value)

	trace(tostring(value))

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
trace(message)

--info("Loaded mod")
