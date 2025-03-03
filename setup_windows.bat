@REM @echo off
@REM echo === Configuration du projet Shoot'emUp ===

@REM call scripts\check_prerequisites.bat
@REM if %errorlevel% neq 0 goto error

@REM call scripts\install_vcpkg.bat
@REM if %errorlevel% neq 0 goto error

@REM call scripts\install_sfml.bat
@REM if %errorlevel% neq 0 goto error

@REM call scripts\configure_project.bat
@REM if %errorlevel% neq 0 goto error

@REM echo === Installation terminee avec succes! ===
@REM goto end

@REM :error
@REM echo Une erreur s'est produite lors de l'installation.
@REM pause
@REM exit /b 1

@REM :end
@REM pause
@REM exit /b 0


@echo off
echo === Configuration du projet ShootemUp ===

cd scripts

:: Verification des prerequis
echo [INFO] Verification des outils necessaires...
call check_prerequisites.bat
if %errorlevel% neq 0 (
    echo [ERREUR] Verification des prerequis echouee.
    pause
    exit /b 1
)

:: Installation de SFML
echo [INFO] Installation de SFML 2.6...
call install_sfml.bat
if %errorlevel% neq 0 (
    echo [ERREUR] Installation de SFML echouee.
    pause
    exit /b 1
)

:: Configuration et compilation du projet
echo [INFO] Configuration et compilation du projet...
call configure_project.bat
if %errorlevel% neq 0 (
    echo [ERREUR] Configuration du projet echouee.
    pause
    exit /b 1
)

cd ..

echo === Installation terminee avec succes! ===
echo.
echo Vous pouvez maintenant lancer le jeu depuis build\Debug\ShootemUp.exe
echo.

pause
exit /b 0