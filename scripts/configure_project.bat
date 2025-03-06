@echo off
setlocal enabledelayedexpansion

echo Configuration du projet avec CMake...
echo ==================================

:: Créer le dossier build s'il n'existe pas
if not exist ..\build mkdir ..\build

:: Se placer dans le dossier build
cd ..\build

:: Déterminer le chemin de CMake à utiliser
set CMAKE_PATH=cmake
if exist "..\cmake\bin\cmake.exe" (
    set CMAKE_PATH=..\cmake\bin\cmake
    echo [INFO] Utilisation de CMake local
) else (
    echo [INFO] Utilisation de CMake systeme
)

:: Configurer le projet avec CMake
echo [INFO] Configuration du projet...
!CMAKE_PATH! ..

:: Vérifier si la configuration a réussi
echo Code de retour apres configuration: !errorlevel!
if !errorlevel! neq 0 (
    echo [ERREUR] Echec de la configuration du projet.
    cd ..\scripts
    exit /b 1
)

:: Compiler le projet
echo [INFO] Compilation du projet...
!CMAKE_PATH! --build . --config Debug

:: Vérifier si la compilation a réussi
echo Code de retour apres compilation: !errorlevel!
if !errorlevel! neq 0 (
    echo [ERREUR] Echec de la compilation du projet.
    cd ..\scripts
    exit /b 1
)

echo [OK] Projet configure et compile avec succes.
echo [INFO] L'executable se trouve dans: build\Debug\

:: Retourner au dossier scripts
cd ..\scripts

exit /b 0