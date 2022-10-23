project "Igalima.Engine"
kind "SharedLib"
language "C#"
dotnetframework "net6.0"

files {
  "**.cs"
}

removefiles {
  "obj/**",
  "bin/**"
}

filter "configurations:Debug"
optimize "Off"
symbols "Default"

filter "configurations:Release"
optimize "On"
symbols "Default"

filter "configurations:Distribution"
optimize "Full"
symbols "Off"
