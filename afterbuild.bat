@echo off
echo.
echo.
echo Copy exe file to target directory (c:/applications/BBDigitalMinutes)
echo.
copy /Y "c:\\Data\\Build\\BBDigitalMinutes.exe" "c:\\applications\\BBDigitalMinutes\\BBDigitalMinutes.exe"
echo.
cd "c:\\applications\\BBDigitalMinutes"
echo.
@BBDigitalMinutes.exe
