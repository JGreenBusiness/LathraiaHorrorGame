@echo off
setlocal enabledelayedexpansion

:: Define file, section, variable
set "config_file=./DefaultEngine.ini"
set "section=[/Game/Developers/ethan/Blueprints/UI/WBP_MainMenu.WBP_MainMenu_C]"
set "variable_name=VersionNumber"

:: Get the latest Git commit hash
for /f "tokens=*" %%i in ('git rev-parse HEAD') do set "new_value=%%i"

:: Check if the section exists
findstr /C:"%section%" "%config_file%" >nul
if %errorlevel% neq 0 (
    echo Adding new section: %section%
    echo %section%>>"%config_file%"
    echo %variable_name%=%new_value%>>"%config_file%"
    echo Section and variable added successfully!
    exit /b
)

:: Use PowerShell script to update the variable
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0generate_version.ps1" "%config_file%" "%section%" "%variable_name%" "%new_value%"

echo Variable updated successfully!