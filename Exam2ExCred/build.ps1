<#
build.ps1 - PowerShell build script for Exam2ExCred
Usage: .\build.ps1
#>

Set-StrictMode -Version Latest

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
Set-Location $scriptDir

Write-Host "Building Exam2ExCred in $scriptDir"

if (Get-Command make -ErrorAction SilentlyContinue) {
    Write-Host "Running make"
    & make
} elseif (Get-Command g++ -ErrorAction SilentlyContinue) {
    Write-Host "make not found; compiling with g++"
    & g++ -std=c++11 -O2 -Wall *.cpp -o exam2excred.exe
} else {
    Write-Error "No build tool found (make or g++). Install MinGW/MSYS2 or Visual Studio Build Tools."
    exit 1
}

Write-Host "Build complete. Running .\exam2excred.exe"
if (Test-Path .\exam2excred.exe) { & .\exam2excred.exe } else { & .\exam2excred }
