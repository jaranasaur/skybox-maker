@echo off
pushd build_debug
cl -Zi ..\src\*.cpp /Fe"skybox-maker.exe"
popd