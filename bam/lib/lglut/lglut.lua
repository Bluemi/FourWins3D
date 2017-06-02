lib = {
	path = PathDir(ModuleFilename()),
}

function lib:configure()
end

function lib:apply(settings)
	settings.cc.includes:Add("usr/include/GL")
	settings.link.libs:Add("glut")
	settings.link.libs:Add("GL")
end
