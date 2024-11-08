@echo off

cd %USERPROFILE%/Desktop/FlappyBird/FlappyBird

tar --create --file=bin\release\FlappyBird.zip res src bin/release/"Flappy bird.exe"