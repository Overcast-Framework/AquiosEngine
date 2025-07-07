file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE CPP_SOURCES "src/*.cpp" "src/**/*.cpp")

set(SOURCES ${CPP_SOURCES} ../vendors/glad/src/glad.c ${HEADER_FILES})

add_library(AquiosEngine SHARED ${SOURCES})

add_custom_command(TARGET AquiosEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:AquiosEngine>
        ${CMAKE_BINARY_DIR}/sandbox)

target_compile_definitions(AquiosEngine PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

target_compile_definitions(AquiosEngine PRIVATE AQUIOSENGINE_EXPORTS)

target_include_directories(AquiosEngine PRIVATE
    src
    ../vendors/glad/include
    ../vendors/glfw/include
    ../vendors/glm
)

if (WIN32)
    target_compile_definitions(AquiosEngine PUBLIC AQ_PLATFORM_WINDOWS)
endif()

source_group("Header Files" FILES ${HEADER_FILES})

find_package(OpenGL REQUIRED)
target_link_libraries(AquiosEngine PRIVATE glfw glm OpenGL::GL)