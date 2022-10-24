es = {}
es.engine = {}
es.engine.dyno = {}
es.loader = {}
es.loader.json = {}

-- es namespace

es.trace = function(message)
    trace(message)
end

es.info = function(message)
    Cinfo(message)
end

es.setModel = function(part, modelName)
    CsetModel(part, modelName)
end

es.setTexture = function(part, textureName)
    CsetTexture(part, textureName)
end

es.loadTexture = function(textureName)
    CloadTexture(textureName)
end

es.synthAdd = function(value)
    CsynthAdd(value)
end

-- es.engine namespace
es.engine.Name = "<NO ENGINE>"
es.engine.RPM = 0
es.engine.Speed = 0
es.engine.Gear = 0
es.engine.Redline = 0
es.engine.AFR = 0

es.engine.Throttle = 0
es.engine.SetThrottle = function(value)
    CsetThrottle(value)
end

es.engine.ManifoldPressure = 0
es.engine.SetManifoldPressure = function(value)
    CsetManifoldPressure(value)
end

es.engine.ExhaustFlow = 0

es.engine.IntakeFlow = 0
es.engine.SetIntakeFlow = function(value)
    CsetIntakeFlow(value)
end

es.engine.setAntilag = function(on, often)
    CsetAntilag(on, often)
end

es.engine.setMixture = function(state)
    CsetMixture(state)
end

es.engine.setIgnition = function(state, minRPM)
    CsetIgnition(state, minRPM)
end

es.engine.setInjection = function(state, minRPM)
    CsetInjection(state, minRPM)
end

es.engine.setCrankWeight = function(value)
    CsetCrankWeight(value)
end

es.engine.setFlywheelWeight = function(value)
    CsetFlywheelWeight(value)
end

es.engine.setPistonWeight = function(value)
    CsetPistonWeight(value)
end

es.engine.setConrodWeight = function(value)
    CsetConrodWeight(value)
end

-- es.engine.dyno namespace

es.engine.dyno.Torque = 0
es.engine.dyno.Power = 0

-- es.loader namespace

es.loader.Version = ""
es.loader.Sim_Version = ""

es.loader.setGlobalInput = function(value)
    CsetGlobalInput(value)
end

es.loader.import = function(filename)
    Cimport(filename)
end

es.loader.initDNet = function()
    CinitDNet()
end

es.loader.sendDNet = function(message)
    CsendDNet(message)
end

-- es.loader.json namespace

es.loader.json.new = function()
    CjsonNew()
end

es.loader.json.addString = function(key, str)
    CjsonAddString(key, str)
end

es.loader.json.addInteger = function(key, integer)
    CjsonAddInt(key, integer)
end

es.loader.json.addNumber = function(key, number)
    CjsonAddNumber(key, number)
end

es.loader.json.getString = function()
    CjsonGetString()

    return JSON_String
end

-- process stuff

function loaderProcess(dt)
    es.engine.Name = Engine_Name

    es.engine.RPM = Engine_RPM
    es.engine.Speed = Engine_Speed
    es.engine.Redline = Engine_Redline
    es.engine.Gear = Engine_Gear

    es.engine.AFR = Engine_AFR
    es.engine.Throttle = Engine_Throttle
    es.engine.ManifoldPressure = Engine_ManifoldPressure
    es.engine.IntakeFlow = Engine_IntakeFlow
    
    es.engine.ExhaustFlow = Engine_ExhaustFlow

    es.engine.dyno.Torque = Dyno_Torque
    es.engine.dyno.Power = Dyno_Power

    es.loader.Version = Loader_Version
    es.loader.SimVersion = Loader_Sim_Version
end

addProcessHandler(loaderProcess)
