@echo off
setlocal enabledelayedexpansion

echo Verification des prerequis...
echo ===========================

echo Checking Visual Studio...

set VS_FOUND=0

:: Check Visual Studio installation folders
if exist "C:\Program Files\Microsoft Visual Studio\2022" (
    echo [OK] Visual Studio 2022 found.
    set VS_FOUND=1
    goto vs_found
)

if exist "C:\Program Files\Microsoft Visual Studio\2019" (
    echo [OK] Visual Studio 2019 found.
    set VS_FOUND=1
    goto vs_found
)

if exist "C:\Program Files (x86)\Microsoft Visual Studio\2022" (
    echo [OK] Visual Studio 2022 found in Program Files (x86).
    set VS_FOUND=1
    goto vs_found
)

if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019" (
    echo [OK] Visual Studio 2019 found in Program Files (x86).
    set VS_FOUND=1
    goto vs_found
)

if %VS_FOUND% equ 0 (
    echo [ERROR] Visual Studio not found.
    exit /b 1
)

:vs_found
echo [OK] Visual Studio is installed.

:: Vérifier si CMake est installé
echo Verification de CMake...
where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERREUR] CMake n'est pas installe ou n'est pas dans le PATH.
    echo Veuillez installer CMake version 3.14 ou superieure.
    echo Vous pouvez le télécharger depuis: https://cmake.org/download/
    exit /b 1
)
echo [OK] CMake trouve.

:: Vérifier la version de CMake
for /f "tokens=3" %%i in ('cmake --version ^| findstr /C:"cmake version"') do (
    set cmake_version=%%i
)
echo Version de CMake detectee: %cmake_version%

:: Vérifier si Git est installé
echo Verification de Git...
where git >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERREUR] Git n'est pas installe ou n'est pas dans le PATH.
    echo Git est necessaire pour cloner vcpkg.
    echo Vous pouvez le télécharger depuis: https://git-scm.com/download/win
    exit /b 1
)
echo [OK] Git trouve.

echo Tous les prerequis sont installes.
exit /b 0