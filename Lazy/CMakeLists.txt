cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)

# for ThirdParty
add_subdirectory(vender)

add_library(Lazy-pbr SHARED 
    Core/Frame.h
    Core/Frame.cpp

    Core/Viewer.h
    Core/Viewer.cpp

    Graphics/Shader.h
    Graphics/Shader.cpp

    Graphics/Texture.h
    Graphics/Texture.cpp
    
    Camera/Camera.h
    Camera/Camera.cpp

    Math/Vec3.h
    Math/Vec3.cpp

    Math/Vec2.h
    Math/Vec2.cpp

    Math/Color.h
    Math/Color.cpp

    Primitives/Ray.h

    Primitives/Primitive.h

    Primitives/Sphere.h
    Primitives/Sphere.cpp
)

target_include_directories(Lazy-pbr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Lazy-pbr PUBLIC GLAD_LIBRARIES)
target_link_libraries(Lazy-pbr PUBLIC glfw)
target_link_libraries(Lazy-pbr PUBLIC png_shared)
