# Debug/Run script for Connectomics-Imaging project
# Usage: .\debug.ps1 [Debug|Release]

param(
    [string]$Config = "Release"
)

$ErrorActionPreference = "Stop"

$BuildDir = "build\"
$ExePath = ".\$BuildDir\Release\app.exe"

if (-not (Test-Path $ExePath)) {
    Write-Host "Executable not found: $ExePath" -ForegroundColor Red
    Write-Host "Build the project first with .\build.ps1" -ForegroundColor Yellow
    exit 1
}

Write-Host "=== Copying vcpkg dependencies ===" -ForegroundColor Green

$VcpkgBinPath = "C:\vcpkg\installed\x64-windows\bin"

if (Test-Path $VcpkgBinPath) {
    Copy-Item "$VcpkgBinPath\*.dll" -Destination $BuildDir -Force -ErrorAction SilentlyContinue
    Write-Host "DLLs copied to build directory" -ForegroundColor Cyan
} else {
    Write-Host "Warning: vcpkg bin directory not found at $VcpkgBinPath" -ForegroundColor Yellow
}

Write-Host "`n=== Running application ===" -ForegroundColor Green
& $ExePath

if ($LASTEXITCODE -ne 0) {
    Write-Host "`nApplication exited with code: $LASTEXITCODE" -ForegroundColor Yellow
}
