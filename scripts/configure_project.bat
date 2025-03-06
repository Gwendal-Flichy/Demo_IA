@echo off
setlocal enabledelayedexpansion

echo Configuration du projet avec CMake...
echo ==================================

:: Créer le dossier build s'il n'existe pas
if not exist ..\build mkdir ..\build

:: Se placer dans le dossier build
cd ..\build

:: Configurer le projet avec CMake (utiliser la version locale si disponible)
echo [INFO] Configuration du projet...
if exist "..\cmake\bin\cmake.exe" (
    echo [INFO] Utilisation de CMake local
    ..\cmake\bin\cmake ..
) else (
    echo [INFO] Utilisation de CMake systeme
    cmake ..
)

:: Vérifier si la configuration a réussi
echo Code de retour après configuration: !errorlevel!
if !errorlevel! neq 0 (
    echo [ERREUR] Echec de la configuration du projet.
    cd ..\scripts
    exit /b 1
)

:: Compiler le projet
echo [INFO] Compilation du projet...
cmake --build . --config Debug

:: Vérifier si la compilation a réussi
echo Code de retour après configuration: !errorlevel!
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