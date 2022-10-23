project "Igalima.Libraries.Glad"
kind "StaticLib"
language "C"
staticruntime "off"

targetdir("bin/" .. OutputDirectory .. "/%{prj.name}")
objdir("bin-int/" .. OutputDirectory .. "/%{prj.name}")

files
{
  "include/glad/glad.h",
  "include/KHR/khrplatform.h",
  "src/glad.c"
}

includedirs
{
  "include"
}

filter "system:windows"
systemversion "latest"

filter "configurations:Debug"
runtime "Debug"
symbols "on"

filter "configurations:Release"
runtime "Release"
optimize "on"
