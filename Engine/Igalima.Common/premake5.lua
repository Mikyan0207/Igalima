project "Igalima.Common"
kind "None"
language "C++"
cppdialect "C++20"
staticruntime "off"

targetdir("%{wks.location}/bin/" .. OutputDirectory .. "/%{prj.name}")
objdir("%{wks.location}/bin-int/" .. OutputDirectory .. "/%{prj.name}")

files
{
  "Headers/**.h"
}
