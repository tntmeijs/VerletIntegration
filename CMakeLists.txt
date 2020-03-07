cmake_minimum_required(VERSION 3.0.0)
project(VerletIntegration)
set(TARGET_NAME VerletIntegration)

set(SRC_FILES src/main.cpp)
set(CORE_FILES
    src/core/window.cpp
    src/core/window.hpp)

add_executable(${TARGET_NAME} ${SRC_FILES} ${CORE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE src)
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

source_group(src FILES ${SRC_FILES})
source_group(src\\core FILES ${CORE_FILES})

if(MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
