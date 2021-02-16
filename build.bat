@echo off

set files= ..\Sources\main.cpp ..\Sources\Platform\Window.cpp
set options= /Zi /Fe"Igalima.OpenGL.exe"

pushd build
:: Change this line if you want to compile on your PC.
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64
cl %options% /I ..\Includes\ /I ..\Sources\ %files% /link /LIBPATH:..\Lib\
popd