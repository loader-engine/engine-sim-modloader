es = {}
es.engine = {}
es.loader = {}

-- es namespace

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
es.engine.AFR = 0
es.engine.Throttle = 0
es.engine.ManifoldPressure = 0
es.engine.ExhaustFlow = 0
es.engine.IntakeFlow = 0

es.engine.setAntilag = function(on, often)
    CsetAntilag(on, often)
end

es.engine.setMixture = function(value)
    CsetMixture(value)
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

-- es.loader namespace

es.loader.Version = ""
es.loader.Sim_Version = ""

es.loader.initDNet = function()
    CinitDNet()
end


-- process stuff

function loaderProcess(dt)
    es.engine.Name = Engine_Name
    es.engine.RPM = Engine_RPM
    es.engine.AFR = Engine_AFR
    es.engine.Throttle = Engine_Throttle
    es.engine.ManifoldPressure = Engine_ManifoldPressure
    es.engine.ExhaustFlow = Engine_ExhaustFlow
    es.engine.IntakeFlow = Engine_IntakeFlow

    es.loader.Version = Loader_Version
    es.loader.SimVersion = Loader_Sim_Version
end

addProcessHandler(loaderProcess)
