file(GLOB CPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp")

add_executable(Sandbox ${CPP_SOURCES})

target_link_libraries(Sandbox PRIVATE AquiosEngine)

target_include_directories(Sandbox PRIVATE ../engine/src)