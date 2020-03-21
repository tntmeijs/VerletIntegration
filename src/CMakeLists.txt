set(SRC_FILES main.cpp)

set(CORE_FILES
    core/window.cpp
    core/window.hpp)

set(GRAPHICS_FILES
    graphics/renderer.cpp
    graphics/renderer.hpp)

set(UTILITY_FILES
    utility/timer.cpp
    utility/timer.hpp
    utility/log.hpp
    utility/literals.hpp)

add_executable(${TARGET_NAME} ${SRC_FILES} ${CORE_FILES} ${GRAPHICS_FILES} ${UTILITY_FILES})

# Includes
target_include_directories(${TARGET_NAME} PRIVATE ./)
target_include_directories(${TARGET_NAME} PRIVATE _deps/glad/GL/include)

# Set compile features such as C++17
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

# Link external libaries
target_link_libraries(${TARGET_NAME} PRIVATE glfw ${GLFW_LIBRARIES})
target_link_libraries(${TARGET_NAME} PRIVATE glm)
target_link_libraries(${TARGET_NAME} PRIVATE glad)

# Make the filter tree look nice in IDEs that support them
source_group(src            FILES ${SRC_FILES})
source_group(src\\core      FILES ${CORE_FILES})
source_group(src\\graphics  FILES ${GRAPHICS_FILES})
source_group(src\\utility   FILES ${UTILITY_FILES})

# Warning level 4 and treat all warnings as errors
if(MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
