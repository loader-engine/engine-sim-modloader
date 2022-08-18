function OnProcess(dt)
	--trace("mod 1 works!")
	if INPUT_R == "true" then
		--trace("pressed full throt")
	end
end

addProcessHandler(OnProcess)
trace("Mod 1 loaded")