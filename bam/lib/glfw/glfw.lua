lib = {
	path = PathDir(ModuleFilename()),
}

function lib:configure()
end

function lib:apply(settings)
	settings.link.libs:Add("GLU")
	settings.link.libs:Add("glfw3")
	settings.link.libs:Add("X11")
	settings.link.libs:Add("Xxf86vm")
	settings.link.libs:Add("Xrandr")
	settings.link.libs:Add("pthread")
	settings.link.libs:Add("Xi")
	settings.link.libs:Add("dl")
	settings.link.libs:Add("Xinerama")
	settings.link.libs:Add("Xcursor")
end
