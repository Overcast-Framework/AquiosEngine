file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(SOURCES ${SOURCE_FILES} ../vendors/glad/src/glad.c ${HEADER_FILES})

add_library(AquiosEngine STATIC ${SOURCES} "src/AquiosEngine/EventSystem.h" "src/AquiosEngine/Events/Event.h" "src/AquiosEngine/Events/KeyEvent.h" "src/AquiosEngine/Events/MouseEvent.h" "src/AquiosEngine/Events/ApplicationEvent.h" "src/AquiosEngine/Events/WindowEvent.h" "src/aqpch.h" "src/aqpch.cpp" "src/AquiosEngine/Window.h" "src/AquiosEngine/Platform/Windows/WindowsWindow.h" "src/AquiosEngine/Platform/Windows/WindowsWindow.cpp" "src/AquiosEngine/Layer.h" "src/AquiosEngine/LayerStack.h" "src/AquiosEngine/LayerStack.cpp" "src/AquiosEngine/ImGui/ImGuiLayer.h" "src/AquiosEngine/ImGui/ImGuiLayer.cpp" "src/AquiosEngine/Input.h" "src/AquiosEngine/Platform/Windows/WindowsInput.h" "../vendors/imgui/imgui.cpp" "../vendors/imgui/imgui_draw.cpp" "../vendors/imgui/imgui_tables.cpp" "../vendors/imgui/imgui_widgets.cpp" "../vendors/imgui/imgui_demo.cpp")

target_compile_definitions(AquiosEngine PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

target_compile_definitions(AquiosEngine PRIVATE AQUIOSENGINE_EXPORTS)

target_include_directories(AquiosEngine PUBLIC
    src
    ../vendors/glad/include
    ../vendors/glfw/include
    ../vendors/glm
    ../vendors/imgui
    ../vendors/spdlog/include
)

if (WIN32)
    target_compile_definitions(AquiosEngine PUBLIC AQ_PLATFORM_WINDOWS)
endif()

target_compile_definitions(AquiosEngine PUBLIC GLFW_INCLUDE_NONE)

target_compile_options(AquiosEngine PRIVATE /utf-8)
target_precompile_headers(AquiosEngine PRIVATE $<$<COMPILE_LANGUAGE:CXX>:aqpch.h>)

# Automatically map folders to VS filters
foreach(FILE ${HEADER_FILES})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/src/" "" REL_PATH ${FILE})
    get_filename_component(DIR "${REL_PATH}" PATH)
    source_group("Header Files\\${DIR}" FILES ${FILE})
endforeach()

foreach(FILE ${SOURCE_FILES})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/src/" "" REL_PATH ${FILE})
    get_filename_component(DIR "${REL_PATH}" PATH)
    source_group("Source Files\\${DIR}" FILES ${FILE})
endforeach()

find_package(OpenGL REQUIRED)
target_link_libraries(AquiosEngine
    PUBLIC glfw glm spdlog OpenGL::GL
)