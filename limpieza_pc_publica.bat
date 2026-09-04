@echo off
setlocal EnableExtensions EnableDelayedExpansion
title Limpieza segura de PC publica
color 0B

:: Este archivo limpia temporales y caches comunes.
:: No elimina Descargas, Documentos, Escritorio ni programas.

fltmc >nul 2>&1
if errorlevel 1 (
    set "ES_ADMIN=0"
) else (
    set "ES_ADMIN=1"
)

cls
echo ==============================================================
echo             LIMPIEZA SEGURA DE PC PUBLICA
echo ==============================================================
echo.
echo Se limpiaran:
echo   - Temporales del usuario actual
echo   - Cache de miniaturas de Windows
echo   - Papelera de reciclaje
echo   - Cache DNS
if "%ES_ADMIN%"=="1" echo   - Temporales generales de Windows
echo.
echo No se borraran Documentos, Descargas, Escritorio ni programas.
echo Cierra navegadores y programas antes de continuar.
echo.

set "RESPUESTA="
set /p "RESPUESTA=Deseas iniciar? (Escribe S y pulsa Enter, o N para cancelar): "
if not defined RESPUESTA goto :cancelado
if /I "%RESPUESTA%"=="S" goto :continuar
if /I "%RESPUESTA%"=="SI" goto :continuar
goto :cancelado

:continuar
set /a PASO=0
set /a TOTAL=5
if "%ES_ADMIN%"=="1" set /a TOTAL=6

call :etapa "Analizando archivos temporales del usuario"
call :animacion 2
call :borrar_con_progreso "%TEMP%" "Temporales del usuario"

call :etapa "Limpiando temporales locales"
call :borrar_con_progreso "%LOCALAPPDATA%\Temp" "Temporales locales"

call :etapa "Limpiando cache de miniaturas"
del /f /q "%LOCALAPPDATA%\Microsoft\Windows\Explorer\thumbcache_*.db" >nul 2>&1
call :animacion 1

call :etapa "Vaciando Papelera de reciclaje"
PowerShell.exe -NoProfile -ExecutionPolicy Bypass -Command "Clear-RecycleBin -Force -ErrorAction SilentlyContinue" >nul 2>&1
call :animacion 1

call :etapa "Limpiando cache DNS"
ipconfig /flushdns >nul 2>&1
call :animacion 1

if "%ES_ADMIN%"=="1" (
    call :etapa "Limpiando temporales generales de Windows"
    call :borrar_con_progreso "%SystemRoot%\Temp" "Temporales de Windows"
)

echo.
echo ==============================================================
echo                    LIMPIEZA TERMINADA
echo ==============================================================
echo.
echo Algunos archivos en uso pudieron conservarse; es normal.
if "%ES_ADMIN%"=="0" (
    echo Para incluir C:\Windows\Temp, ejecuta este archivo como administrador.
)
echo Es recomendable cerrar sesion o reiniciar esta PC publica.
echo.
pause
exit /b 0

:etapa
set /a PASO+=1
set /a GLOBAL=PASO*100/TOTAL
echo.
echo --------------------------------------------------------------
echo [Progreso aproximado: !GLOBAL!%%] Paso !PASO! de !TOTAL!
echo %~1...
exit /b

:borrar_con_progreso
set "RUTA=%~1"
set "NOMBRE=%~2"
if not defined RUTA exit /b
if not exist "%RUTA%" (
    echo [----------] 100%%  No existe la carpeta: %NOMBRE%
    exit /b
)

set "RUTA_LIMPIEZA=%RUTA%"
set "NOMBRE_LIMPIEZA=%NOMBRE%"
PowerShell.exe -NoLogo -NoProfile -ExecutionPolicy Bypass -Command ^
 "$p=$env:RUTA_LIMPIEZA; $n=$env:NOMBRE_LIMPIEZA;" ^
 "$files=@(Get-ChildItem -LiteralPath $p -File -Recurse -Force -ErrorAction SilentlyContinue);" ^
 "$total=$files.Count; $done=0; $bytes=[int64]0;" ^
 "if($total -eq 0){Write-Host ('[##########] 100%%  '+$n+': nada que borrar'); exit};" ^
 "foreach($f in $files){$size=$f.Length; Remove-Item -LiteralPath $f.FullName -Force -ErrorAction SilentlyContinue; if(-not (Test-Path -LiteralPath $f.FullName)){$bytes+=$size}; $done++; $pct=[int](100*$done/$total); $bars=[int]($pct/10); $bar=('#'*$bars)+('-'*(10-$bars)); Write-Progress -Activity ('Limpiando '+$n) -Status ($done.ToString()+' de '+$total+' archivos') -PercentComplete $pct; if(($done%%100)-eq 0 -or $done-eq $total){Write-Host ('[{0}] {1,3}%%  {2}/{3} archivos' -f $bar,$pct,$done,$total)}};" ^
 "Get-ChildItem -LiteralPath $p -Directory -Recurse -Force -ErrorAction SilentlyContinue | Sort-Object FullName -Descending | Remove-Item -Force -ErrorAction SilentlyContinue;" ^
 "Write-Progress -Activity ('Limpiando '+$n) -Completed; Write-Host ''; Write-Host ('Liberado aproximadamente: '+[math]::Round($bytes/1MB,2)+' MB')"
exit /b

:animacion
set /a VUELTAS=%~1*4
set "GIRO=|/-\"
<nul set /p="Procesando "
for /L %%G in (1,1,!VUELTAS!) do (
    set /a POS=(%%G-1)%%4
    for %%P in (!POS!) do set "CHAR=!GIRO:~%%P,1!"
    <nul set /p="!CHAR!."
    >nul ping 127.0.0.1 -n 2 -w 250
)
echo  listo.
exit /b

:cancelado
echo.
echo Limpieza cancelada. No se modifico nada.
timeout /t 2 /nobreak >nul
exit /b 0
