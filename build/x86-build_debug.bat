
:: Copyright (c) 2016 Juan Delgado (JuDelCo)
:: License: GPLv3 License
:: GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

@echo off

set PATH=%PATH%;C:\Programacion\CppLibs\TDM-GCC_4.9.2-x86\bin
set PATH=%PATH%;C:\Programacion\CppLibs\CMake_3.1.0-x86\bin
set DIR=%CD%

:build

cd %DIR%
cd ../

cls
cmake -D BUILD_CPU_ARCH:STRING=x86 -D CMAKE_BUILD_TYPE:STRING=Debug -D CMAKE_INSTALL_PREFIX:PATH="" build/x86_Debug/
cls
cmake -L -N build/x86_Debug/
echo.

cd build/x86_Debug
mingw32-make all

echo.
echo Press any key to build again (or press CTRL+C to exit) ...
pause > nul

goto :build
