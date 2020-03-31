set(SRC_FILES main.cpp)

set(CORE_FILES
    core/window.cpp
    core/window.hpp
    core/keycodes.hpp)

set(OPENGL_FILES
    graphics/opengl/gl_renderer.cpp
    graphics/opengl/gl_renderer.hpp
    graphics/opengl/gl_shader.cpp
    graphics/opengl/gl_shader.hpp
    graphics/opengl/gl_mesh.cpp
    graphics/opengl/gl_mesh.hpp)

set(GRAPHICS_FILES
    graphics/renderer.cpp
    graphics/renderer.hpp
    graphics/shader.hpp
    graphics/graphics_enums.hpp
    graphics/mesh.hpp
    graphics/vertex.hpp)

set(UTILITY_FILES
    utility/timer.cpp
    utility/timer.hpp
    utility/log.hpp
    utility/literals.hpp)

add_executable(${TARGET_NAME} ${SRC_FILES} ${CORE_FILES} ${GRAPHICS_FILES} ${UTILITY_FILES} ${OPENGL_FILES})

# Includes
target_include_directories(${TARGET_NAME} PRIVATE ./)
target_include_directories(${TARGET_NAME} PRIVATE ../_deps/glad/GL/include)

# Set compile features such as C++17
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)
target_compile_definitions(${TARGET_NAME} PRIVATE GLFW_INCLUDE_NONE)

# Link external libaries
target_link_libraries(${TARGET_NAME} PRIVATE glfw ${GLFW_LIBRARIES})
target_link_libraries(${TARGET_NAME} PRIVATE glm)
target_link_libraries(${TARGET_NAME} PRIVATE glad)

# Make the filter tree look nice in IDEs that support them
source_group(src                    FILES ${SRC_FILES})
source_group(src\\core              FILES ${CORE_FILES})
source_group(src\\graphics          FILES ${GRAPHICS_FILES})
source_group(src\\graphics\\opengl  FILES ${OPENGL_FILES})
source_group(src\\utility           FILES ${UTILITY_FILES})

# Warning level 4 and treat all warnings as errors
if(MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)
