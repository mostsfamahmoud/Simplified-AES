@echo off
setlocal enabledelayedexpansion

set "file=mytestcases.txt"

for /f "tokens=1,2,3,4" %%a in (%file%) do (
    echo %%a %%b %%c %%d
    SAES_test.exe %%a %%b %%c %%d
    echo.
)

endlocal