
@echo off

set PATH=%PATH%;C:\Programacion\CppLibs\TDM-GCC_4.9.2-x64\bin
set PATH=%PATH%;C:\Programacion\CppLibs\CMake_3.1.0-x64\bin
set DIR=%CD%

:build

cd %DIR%
cd ../

cls
cmake -D BUILD_CPU_ARCH:STRING=x64 -D CMAKE_BUILD_TYPE:STRING=Debug -D CMAKE_INSTALL_PREFIX:PATH="" build/x64_Debug/
cls
cmake -L -N build/x64_Debug/
echo.

cd build/x64_Debug
mingw32-make install

:run

echo.
cd ../../bin/
Game_Debug_x64.exe
