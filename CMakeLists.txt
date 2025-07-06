cmake_minimum_required(VERSION 3.15)

project(AquiosEngine VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendors/glfw)
add_subdirectory(vendors/glm)

file(GLOB CPP_SOURCES "src/*.cpp" "src/**/*.cpp")
set(SOURCES ${CPP_SOURCES} vendors/glad/src/glad.c)

add_executable(AquiosEngine ${SOURCES})

target_compile_definitions(AquiosEngine PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

target_include_directories(AquiosEngine PRIVATE
    src
    vendors/glad/include
)

find_package(OpenGL REQUIRED)
target_link_libraries(AquiosEngine PRIVATE glfw glm OpenGL::GL)