myShittyVar = "hello there"

function OnProcess(dt)
	trace("Engine info:")

	if Engine_Name == nil then
		trace("Engine name is nil")
	end

	trace(string.format("Engine Name: %s", Engine_Name))
	trace(string.format("RPM: %s", Engine_RPM))
	trace(string.format("AFR: %s", Engine_AFR))
	trace(string.format("Throttle: %s", Engine_Throttle))
	trace(string.format("Manifold pressure: %s", Engine_ManifoldPressure))

	trace(myShittyVar)
end

addProcessHandler(OnProcess)
trace("Mod 2 loaded")