@echo off

cd %USERPROFILE%\Desktop\FlappyBird\FlappyBird

if not exist "bin\release" 
(
    mkdir "bin\release"
)

tar --create --file=bin\release\FlappyBird.zip res src bin/release/"Flappy bird.exe"