@echo off
setlocal
where g++ >nul 2>&1
if errorlevel 1 (
  echo g++ non trovato.
  echo Installa MinGW-w64 e assicurati che g++ sia nel PATH.
  pause
  exit /b 1
)
g++ -std=c++17 -O2 -o InsuraPro_CRM.exe main.cpp
if errorlevel 1 (
  echo.
  echo Compilazione fallita.
  pause
  exit /b 1
)
echo.
echo Compilazione completata: InsuraPro_CRM.exe
pause
