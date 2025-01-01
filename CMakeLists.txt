cmake_minimum_required(VERSION 3.31)

project(biometric_cryptography)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(biometric_cryptography
    src/main.cpp
    src/data_IO/image_IO.cpp
    src/data_IO/image_IO.hpp
    src/image_processing/preprocessing/contrast_enhancement.cpp
    src/image_processing/preprocessing/contrast_enhancement.hpp
    src/biometrics/feature_extraction.cpp
    src/biometrics/feature_extraction.hpp
)

target_link_libraries(biometric_cryptography
    m
    ${OpenCV_LIBS}
)
