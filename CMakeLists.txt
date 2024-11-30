cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(SandBox)

find_package(Vulkan REQUIRED)
# main Lazy library
add_subdirectory(vender)

add_executable(${PROJECT_NAME} 
    
    main.cpp
    
    pch.h

    window.h
    window.cpp

    log.h
    log.cpp

    core.h
    core.cpp

    utils.h
    utils.cpp

    engine.h
    engine.cpp
)

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glm::glm-header-only)
target_link_libraries(${PROJECT_NAME} assimp)