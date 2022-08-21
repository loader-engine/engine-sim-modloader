-- EXAMPLE GLOBAL VARIABLES:
ModName = "Turbo Mod"
ModDescription = "TurboCharger mod"
ModVersion = "0.0.1"

spool = 0
spoolBoostMult = 0.00001
spoolMult = 100
frictionSub = 0.001
wastegateTrigger = 5
pressMult = 2000
outputPressDiv = 5
threshold = 0.00001

function OnProcess(dt)
	
	-- this function is executed on EngineSimApplication::process()
	-- avaiable vars and functions are listed in the documentation

	-- add the spool and stuff
	flow = tonumber(Engine_ExhaustFlow)
	throttle = tonumber(Engine_Throttle)
	throttle = throttle * -1
	throttle = throttle +1

	if flow < 1 then
		flow = -flow
	end

	if flow < threshold then
		flow = 0
		spool = spool - frictionSub;
	end

	result = flow * pressMult;

	spool = spool +result;

	if throttle == 0 then
		if spool > -0.5 then
			spool = spool - 0.25
		end
	end

	if spool >= wastegateTrigger then
		spool = wastegateTrigger
	elseif spool < -0.5 then
		spool = -0.5
	end

	-- apply the press and flow
	i = spool / outputPressDiv
	i = i * throttle
	Engine_ManifoldPressure = i

	i = spool * spoolBoostMult
	i = i * throttle
	Engine_IntakeFlow = i;

end

function OnStart()
	
	-- this function is executed on EngineSimApplication::initialize()
	-- before anything executes
	-- there is no input here!

end

addStartHandler(OnStart)
addProcessHandler(OnProcess)
message = string.format("Loaded Turbo Mod %s", ModVersion)
trace(message)

--info("Loaded mod")
