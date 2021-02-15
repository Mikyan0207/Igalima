@echo off

:: Run once to enable cl.
:: Change this line if you want to compile on your PC.
pushd build
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64
popd