@echo off
pushd build
cl ..\src\*.cpp /Fe"main.exe"
popd