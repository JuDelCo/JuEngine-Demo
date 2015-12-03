
@echo off

set PATH=%PATH%;C:\Programacion\CppLibs\TDM-GCC_4.9.2-x86\bin

cls
cd x86_Debug
mingw32-make clean
cd ../x86_Release
mingw32-make clean

echo.
echo Build files cleaned !
echo.
echo Press any key to exit ...
pause > nul
