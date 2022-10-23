project "Igalima.Scripting"
kind "StaticLib"
language "C++"
cppdialect "C++20"
staticruntime "off"

targetdir("%{wks.location}/bin/" .. OutputDirectory .. "/%{prj.name}")
objdir("%{wks.location}/bin-int/" .. OutputDirectory .. "/%{prj.name}")

files
{
  "Headers/**.h",
  "Source/**.cpp"
}

defines
{
  "_CRT_SECURE_NO_WARNINGS"
}

includedirs
{
  "Headers",
  "%{IncludeDirectories.hostfxr}"
}

flags
{
  "NoPCH"
}

filter "configurations:Debug"
defines "IG_DEBUG"
runtime "Debug"
symbols "on"

filter "configurations:Release"
defines "IG_RELEASE"
runtime "Release"
optimize "on"

filter "configurations:Distribution"
defines "IG_DISTRIBUTION"
runtime "Release"
optimize "on"
