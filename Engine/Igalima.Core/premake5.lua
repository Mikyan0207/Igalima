project "Igalima.Core"
kind "StaticLib"
language "C++"
cppdialect "C++20"

targetdir("bin/" .. OutputDirectory .. "/%{prj.name}")
objdir("bin-int/" .. OutputDirectory .. "/%{prj.name}")

files
{
  "Headers/**.h",
  "Source/**.cpp"
}

includedirs
{
  "Headers",
  "%{wks.location}/Engine/Igalima.Common/Headers",
  "%{wks.location}/Engine/Igalima.Grahpics/Headers"
}

links
{
  "Igalima.Common",
  "Igalima.Graphics"
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
