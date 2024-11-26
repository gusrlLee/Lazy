cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(LazyPBR)

# main Lazy library
add_subdirectory(vender)

add_executable(${PROJECT_NAME} 
    main.cpp
)



