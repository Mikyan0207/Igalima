@echo off

set opts=-FC -GR- -EHa- -nologo -Zi
set code=%cd%
pushd build
cl %opts% %code%\win32 -FeIgalima.OpenGL
popd
