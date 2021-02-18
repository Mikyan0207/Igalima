@echo off

:: Visual Studio CL compiler path.
:: Change this line if you want to compile on your PC.
set CLCompilerPath= "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat"

:: Source files.
set SourceFiles= ..\Sources\Renderer\Renderer.cpp ..\Sources\OS\Win32.cpp ..\Sources\glad.c

:: Inclues files directory.
set DebugIncludeFiles= /I"D:\GitHub\Igalima.OpenGL\Includes" /I"..\Sources"

:: Libraries
set DebugLibraries= /DYNAMICBASE "opengl32.lib" "user32.lib" "gdi32.lib" "shell32.lib"

:: Debug Compiler Flags.
set DebugCompilerOptions= /DDEBUG /MDd /nologo /GR /Od /Oi /WX /W4 /Zi /EHsc /std:c++17 /Fe"Igalima.OpenGL.exe"

:: Linker Flags.
set DebugLinkerOptions=

pushd build
call %CLCompilerPath% x64
cl %DebugCompilerOptions% %DebugIncludeFiles% %SourceFiles% %DebugLibraries%  %DebugLinkerOptions%
popd