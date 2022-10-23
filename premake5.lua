include "Dependencies.lua"

workspace "Igalima"
architecture "x86_64"
platforms "Win64"
startproject "Igalima.Editor"

configurations
{
  "Debug",
  "Release",
  "Distribution"
}

flags
{
  "MultiProcessorCompile"
}

OutputDirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Libraries"
include "Libraries/Glad"
include "Libraries/hostfxr"
group ""

group "Engine"
include "Engine/Igalima.Common"
include "Engine/Igalima.Core"
include "Engine/Igalima.Graphics"
group ""

group "Platforms"
include "Engine/Igalima.Win32"
group ""

group "Scripting"
include "Scripting/Igalima.Engine"
include "Scripting/Igalima.Scripting"
group ""

group "Editor"
include "Editor/Igalima.Editor"
group ""
