cmake_minimum_required(VERSION 4.2)
project(Codexzier_Versatron)

set(CMAKE_CXX_STANDARD 14)

include_directories(.
    "$ENV{HOME}/Arduino/libraries"
    "$ENV{HOME}/Arduino/libraries/GC9A01_LTSM/src"
    "$ENV{HOME}/Arduino/libraries/display16_LTSM/src"
)

add_executable(Codexzier_Versatron
        Codexzier_Versatron.cpp
        Codexzier_Versatron.h
        ControlRingSegmentDisplay.cpp
        ControlRingSegmentDisplay.h
        MenuArea.cpp
        MenuArea.h
        MenuPaging.cpp
        MenuPaging.h
        AppWorkout.cpp
        AppWorkout.h
        AppWorkoutSetup.cpp
        AppWorkoutSetup.h)
