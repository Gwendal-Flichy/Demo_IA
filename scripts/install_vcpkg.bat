@REM @echo off
@REM echo Verification et installation de vcpkg...
@REM echo ========================================

@REM :: Se placer dans le dossier parent (racine du projet)
@REM cd ..

@REM :: Vérifier si vcpkg existe déjà
@REM if exist vcpkg (
@REM     echo vcpkg est deja installe.
@REM ) else (
@REM     :: Cloner vcpkg
@REM     git clone https://github.com/microsoft/vcpkg.git
    
@REM     :: Exécuter bootstrap
@REM     cd vcpkg
@REM     call bootstrap-vcpkg.bat
@REM     cd ..
    
@REM     echo vcpkg a ete installe.
@REM )

@REM :: Retourner au dossier scripts
@REM cd scripts

@REM pause

@REM echo Installation de vcpkg terminee.
@REM exit /b 0