rem toolPath, "-c", dataPath, "-p", spiPage+"", "-b", spiBlock+"", "-s", (spiEnd - spiStart)+"", imagePath

set LOCALPATH=%~dp0
set BUILD_PATH=%LOCALPATH%..\build
set HOME=%HOMEDRIVE%%HOMEPATH%

mkdir %BUILD_PATH%
set TOOL_PATH=%HOME%\AppData\Local\Arduino15\packages\esp8266\tools\mklittlefs\2.5.0-4-fe5bb56\mklittlefs.exe
%TOOL_PATH% -c ../data -p 256 -b 8192 -s 2072576 %BUILD_PATH%\littlefs.bin
pause