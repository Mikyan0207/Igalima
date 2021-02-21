@echo off

set CLCompilerPath= "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat"


:: Source files.
set SourceFiles= ..\Sources\main.cpp ..\Sources\OS\Win32\Win32Window.cpp ..\Sources\OS\Win32\Win32XInput.cpp ..\Sources\Memory\StackAllocator.cpp ..\Sources\glad.c

:: Inclues files directory.
set DebugIncludeFiles= /I"..\Includes" /I"..\Sources"

:: Libraries
set DebugLibraries= "opengl32.lib" "user32.lib" "gdi32.lib" "winmm.lib"

:: Debug Compiler Flags.
set DebugCompilerOptions= /DDEBUG /MDd /nologo /GR /Od /Oi /WX /W4 /Zi /EHsc /std:c++17 /Fe"Igalima" /Fm"Igalima.map"

:: Linker Flags.
set DebugLinkerOptions=

IF NOT EXIST build-exe mkdir build-exe

pushd build-exe
call %CLCompilerPath% x64
cl %DebugCompilerOptions% %DebugIncludeFiles% %SourceFiles% %DebugLibraries% %DebugLinkerOptions%
popd
