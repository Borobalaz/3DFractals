# Clean build artifacts script
# Usage: .\clean.ps1

$ErrorActionPreference = "Stop"

Write-Host "=== Cleaning build directory ===" -ForegroundColor Green

if (Test-Path "build") {
    Remove-Item -Recurse -Force "build"
    Write-Host "Build directory removed" -ForegroundColor Cyan
} else {
    Write-Host "Build directory does not exist" -ForegroundColor Yellow
}

Write-Host "Clean completed." -ForegroundColor Green
