cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)

# for ThirdParty
add_subdirectory(vender)

add_library(Lazy-pbr SHARED 
    Math/Vec3.h
    Math/Vec3.cpp

    Math/Vec2.h
    Math/Vec2.cpp

    Primitives/Ray.h
)

target_include_directories(Lazy-pbr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Lazy-pbr PUBLIC glfw GLAD_LIBRARIES)
