@echo off
setlocal enabledelayedexpansion
echo Installation locale de SFML 2.6...
echo ================================

:: Créer le dossier external s'il n'existe pas
if not exist ..\external mkdir ..\external

:: Définir le chemin de destination
set SFML_DIR=..\external\SFML-2.6.0

:: Vérifier si SFML est déjà téléchargé
if exist %SFML_DIR% (
    echo [INFO] SFML 2.6 est deja installe dans %SFML_DIR%
) else (
    :: Télécharger SFML 2.6
    echo [INFO] Telechargement de SFML 2.6...
    
    :: URL de téléchargement fixe (sans utiliser de variables dans PowerShell)
    powershell -Command "Invoke-WebRequest -Uri 'https://www.sfml-dev.org/files/SFML-2.6.0-windows-vc17-64-bit.zip' -OutFile '..\external\sfml.zip'"
    
    if !errorlevel! neq 0 (
        echo [ERREUR] Echec du telechargement de SFML.
        exit /b 1
    )
    
    :: Extraire le ZIP
    echo [INFO] Extraction de SFML...
    powershell -Command "Expand-Archive -Path '..\external\sfml.zip' -DestinationPath '..\external'"
    
    if !errorlevel! neq 0 (
        echo [ERREUR] Echec de l'extraction de SFML.
        exit /b 1
    )
    
    :: Nettoyer
    del ..\external\sfml.zip
    
    echo [OK] SFML 2.6 a ete telecharge et extrait.
)

:: Vérifier si l'installation a réussi
if not exist %SFML_DIR%\lib\cmake\SFML\SFMLConfig.cmake (
    echo [ERREUR] Installation de SFML 2.6 incomplete ou invalide.
    exit /b 1
)

echo [INFO] SFML 2.6 est pret a etre utilise.

exit /b 0