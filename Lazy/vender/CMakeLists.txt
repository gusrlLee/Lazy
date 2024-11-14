cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)

# GLFW Library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

# GLAD library
add_subdirectory(glad)

# For save to result image
set(PNG_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(libpng)
