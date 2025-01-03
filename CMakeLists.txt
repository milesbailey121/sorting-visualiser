set(CMAKE_C_COMPILER "D:/MinGw/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "D:/MinGw/bin/g++.exe")

cmake_minimum_required(VERSION 3.28)
project(sorting-visualiser LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main 
    src/main.cpp
    src/Sound/SoundGenerator.cpp
    src/Window/Assets/Button.cpp
    src/Window/Assets/Slider.cpp
    src/Window/Assets/RadioButton.cpp
    src/Window/Visualisation.cpp
    src/Window/GUI.cpp
    src/Algorithms/Algorithms.cpp
    src/Algorithms/SortingState.cpp
)   
#src/SortingUI.cpp
#src/SortingAlgorithms.cpp  
#src/AlgorithmStats.cpp
target_link_libraries(main PRIVATE sfml-graphics sfml-audio)
target_compile_features(main PRIVATE cxx_std_17)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
