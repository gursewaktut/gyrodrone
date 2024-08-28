# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
include(${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

# Change project name to 'drone'
project(drone C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is 'drone', version 0.1
if (TARGET tinyusb_device)
    add_executable(drone
            main.c
            mpu6050_i2c.c
            kalman.c
    )

    # Pull in common dependencies and additional i2c hardware support
    target_link_libraries(drone pico_stdlib hardware_i2c)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(gyro 1)
    pico_enable_stdio_uart(gyro 0)

    # Create map/bin/hex file etc.
    pico_add_extra_outputs(drone)

    # add url via pico_set_program_url
    # (you can add a link to a relevant project page or documentation here)
elseif(PICO_ON_DEVICE)
    message("Skipping hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()
