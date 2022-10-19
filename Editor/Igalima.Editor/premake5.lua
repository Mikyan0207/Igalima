project "Igalima.Editor"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"
staticruntime "off"

targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

files {
  "Source/**.cpp",
  "Headers/**.h"
}

removefiles {
  "obj/**",
  "bin/**"
}

includedirs {
  "%{wks.location}/Engine/Igalima.Core/Headers"
}

links {
  "Igalima.Scripting"
}

filter "system:windows"
systemversion "latest"

filter "configurations:Debug"
defines "IGALIMA_DEBUG"
runtime "Debug"
symbols "on"

filter "configurations:Release"
defines "IGALIMA_RELEASE"
runtime "Release"
optimize "on"

filter "configurations:Dist"
defines "IGALIMA_DIST"
runtime "Release"
optimize "on"
