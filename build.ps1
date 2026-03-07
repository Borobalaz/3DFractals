# Build script for Connectomics-Imaging project
# Usage: .\build.ps1 [Debug|Release]

param(
    [string]$Config = "Release"
)

$ErrorActionPreference = "Stop"

Write-Host "=== Configuring CMake ===" -ForegroundColor Green
cmake -S . -B build `
    -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" `
    -DCMAKE_BUILD_TYPE=$Config

if ($LASTEXITCODE -ne 0) {
    Write-Host "CMake configuration failed!" -ForegroundColor Red
    exit 1
}

Write-Host "`n=== Building the project ===" -ForegroundColor Green
cmake --build build --config $Config

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed!" -ForegroundColor Red
    exit 1
}

Write-Host "`n=== Build completed successfully ===" -ForegroundColor Green
Write-Host "Executable: build\$Config\app.exe" -ForegroundColor Cyan
