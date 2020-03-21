cmake_minimum_required(VERSION 3.0.0)
project(VerletIntegration)
set(TARGET_NAME VerletIntegration)

# GLFW
add_subdirectory(_deps/glfw)
include_directories(_deps/glfw/include)

# GLM
find_package(glm REQUIRED)

# GLAD
add_library(glad STATIC
    _deps/glad/GL/src/glad.c
    _deps/glad/GL/include/glad/glad.h
    _deps/glad/GL/include/KHR/khrplatform.h)
target_include_directories(glad PRIVATE _deps/glad/GL/include)

# Project
add_subdirectory(src)
