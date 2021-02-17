@echo off

set files= ..\Sources\main.cpp ..\Sources\Platform\Window.cpp ..\Sources\Renderer\Renderer.cpp ..\Sources\glad.c
set options= /DDEBUG /Zi /EHsc /W3 /std:c++17 /MDd /Fe"Igalima.OpenGL.exe"

pushd build
:: Change this line if you want to compile on your PC.
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64
cl %options% /I"D:\GitHub\Igalima.OpenGL\Includes" /I"..\Sources" %files% /DYNAMICBASE "glfw3.lib" "user32.lib" "gdi32.lib" "shell32.lib" /link /LIBPATH:..\Lib\
popd