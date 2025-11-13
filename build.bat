@echo off
SET "BuildExe=nbuild.exe"

IF EXIST "%BuildExe%" (
  echo Building project...
  ./build.exe
) ELSE (
  echo Bootstraping build...
  cc nob.c -o build.exe
)