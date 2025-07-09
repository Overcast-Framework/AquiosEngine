cmake_minimum_required(VERSION 3.15)
project(AquiosEngine VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendors/glfw)
add_subdirectory(vendors/glm)
add_subdirectory(vendors/imgui)
add_subdirectory(vendors/spdlog)

add_subdirectory(engine)
add_subdirectory(sandbox)
