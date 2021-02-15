#!/bin/bash

code="$PWD"
opts=-g
cd build > /dev/null
g++ $opts $code/x64 -o Igalima.OpenGL
cd $code > /dev/null
