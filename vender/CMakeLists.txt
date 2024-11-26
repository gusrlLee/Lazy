cmake_minimum_required(VERSION 3.20)

# glfw 
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

# glm 
add_subdirectory(glm)

# assimp 
add_subdirectory(assimp)