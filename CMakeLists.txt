cmake_minimum_required(VERSION 3.12)
project(Lab_3_3D_scene)

set(CMAKE_CXX_STANDARD 14)

add_library(gdi32 STATIC IMPORTED Drawing/Model3D.h Drawing/Camera3D.h)
set_property(TARGET gdi32 PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/gdi32.lib)
add_dependencies(gdi32 project_gdi32)


add_executable(Lab_3_3D_scene
        main.cpp
        Drawing/Camera2D.h
        Drawing/Model2D.h
        Drawing/Scene2D.h
        Math/AffineTransform.h
        Math/Matrix.h
        )


target_link_libraries(${PROJECT_NAME} gdi32)