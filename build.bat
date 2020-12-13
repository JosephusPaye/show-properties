@echo off

:: include the environment variables
call env.bat

:: add the paths to PATH
SET PATH=%PATH%;%CL_PATH%;%VSDEVCMD_PATH%

:: setup the environment for cl.exe compilation
:: (needed to find system include headers)
call VsDevCmd.bat

:: compile the code
cl.exe /EHsc /O1 src\show-properties.cpp

:: delete the intermediate object file and ignore any errors
del show-properties.obj 2>nul

:: create the bin folder if it doesn't exist
if not exist "bin" mkdir "bin"

:: move the compiled binary to the bin folder
move show-properties.exe bin\ShowProperties.exe
