cmake_minimum_required(VERSION 4.2)
project(Codexzier_Versatron)

set(CMAKE_CXX_STANDARD 20)

include_directories(.
    "$ENV{HOME}/Arduino/libraries"
    "$ENV{HOME}/Arduino/libraries/GC9A01_LTSM/src"
    "$ENV{HOME}/Arduino/libraries/display16_LTSM/src"

    "$ENV{HOME}/.arduino15/packages/esp32/hardware/esp32/3.3.10/cores/esp32"
    "$ENV{HOME}/.arduino15/packages/esp32/hardware/esp32/3.3.10/variants/XIAO_ESP32S3"

    "$ENV{HOME}/.arduino15/packages/esp32/hardware/esp32/3.3.10/libraries/FS/src"
    "$ENV{HOME}/.arduino15/packages/esp32/hardware/esp32/3.3.10/libraries/SD/src"
    "$ENV{HOME}/.arduino15/packages/esp32/hardware/esp32/3.3.10/libraries/SPI/src"
    "$ENV{HOME}/.arduino15/packages/esp32/hardware/esp32/3.3.10/libraries/WiFi/src"

    "$ENV{HOME}/.arduino15/packages/esp32/tools/esp32s3-libs/3.3.10/include/espressif__esp32-camera/driver/include"
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
        AppWorkoutSetup.h
        AppWorkoutRun.cpp
        AppWorkoutRun.h
        AppTorchRun.cpp
        AppTorchRun.h
        AppCameraRun.cpp
        AppCameraRun.h
        AppWlanScanner.cpp
        AppWlanScanner.h
        AppWlanScannerResultList.cpp
        AppWlanScannerResultList.h
        AppBleScanner.cpp
        AppBleScanner.h
        AppBleScannerResultList.cpp
        AppBleScannerResultList.h
        AppPictureViewer.cpp
        AppPictureViewer.h
        IDrawable.h
        BaseDrawable.h
        AppRadioRadar.cpp
        AppRadioRadar.h
        SubFileManager.cpp
        SubFileManager.h)
