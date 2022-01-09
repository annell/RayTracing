cmake_minimum_required(VERSION 3.17)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracing
        main.cpp
        sphere.cpp
        hittable_list.cpp
        camera.cpp
        camera.h
        material.h
        cube.cpp
        cube.h
        )

target_link_libraries(
        RayTracing
        "-framework Foundation"
        "-framework QuartzCore"
        "-framework Metal"
)
