
@echo off

set PATH=%PATH%;C:\Programacion\CppLibs\TDM-GCC_4.9.2-x64\bin

cls
cd x64_Debug
mingw32-make clean
cd ../x64_Release
mingw32-make clean

echo.
echo Build files cleaned !
echo.
echo Press any key to exit ...
pause > nul
