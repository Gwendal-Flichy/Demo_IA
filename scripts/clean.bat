@echo off
echo suppresssion du build, du cmake et du external pour recommencer l'installation
echo ====================================================================

cd ..
if exist build rmdir /s /q build
echo dossier build supprimer

if exist external rmdir /s /q external
echo dossier external supprimer

if exist cmake rmdir /s /q cmake
echo dossier cmake supprimer

cd scripts

pause
exit /b 0