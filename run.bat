@echo off
rem Create build directory if it doesn't exist
if not exist "d:/GitHub/sorting-visualiser/build" (
    mkdir "d:/GitHub/sorting-visualiser/build"
)

rem Run CMake to generate the makefiles
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE --no-warn-unused-cli -S D:/GitHub/sorting-visualiser -B d:/GitHub/sorting-visualiser/build

rem Move to the build directory
cd d:/GitHub/sorting-visualiser/build

rem Build the project with mingw32-make
mingw32-make

rem Check if main.exe exists before attempting to run it
if exist "bin/main.exe" (
    rem Run the compiled program
    bin\main.exe
) else if exist "./build/bin/main.exe" (
    rem Alternative path in case the executable is in ./build/bin/
    .\build\bin\main.exe
) else (
    echo main.exe not found. Build might have failed.
    pause
    exit /b 1
)
