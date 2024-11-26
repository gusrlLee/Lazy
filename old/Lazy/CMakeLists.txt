cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)

# for ThirdParty
add_subdirectory(vender)

add_library(Lazy-pbr SHARED 
    # CORE 
    Core/Frame.h
    Core/Frame.cpp
    Core/Viewer.h
    Core/Viewer.cpp
    Core/Renderer.h
    Core/Renderer.cpp

    # GRAPHICS 
    Graphics/Shader.h
    Graphics/Shader.cpp
    Graphics/Texture.h
    Graphics/Texture.cpp
    Graphics/Quad.h
    Graphics/Quad.cpp
    
    # CAMERA 
    Camera/Camera.h
    Camera/Camera.cpp

    # MATH
    Math/Vec3.h
    Math/Vec3.cpp
    Math/Vec2.h
    Math/Vec2.cpp
    Math/Color.h
    Math/Color.cpp

    # PRIMITIVES
    Primitives/Ray.h
    Primitives/Primitive.h
    Primitives/Sphere.h
    Primitives/Sphere.cpp
)

target_include_directories(Lazy-pbr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Lazy-pbr PUBLIC GLAD_LIBRARIES)
target_link_libraries(Lazy-pbr PUBLIC glfw)
target_link_libraries(Lazy-pbr PUBLIC png_shared)
