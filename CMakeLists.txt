cmake_minimum_required(VERSION 3.15)
project(MyEngine VERSION 1.0.0 LANGUAGES CXX C)
find_package(glfw3 3.3 REQUIRED)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опции компилятора
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -g -Wno-deprecated)
endif()

# --- INCLUDE ---
# 1. Стандартные зависимости (GLFW, Glad)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/include)
# 2. ImGui (чтобы писать #include <imgui.h>)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/include/imgui)

# --- SOURCES ---
# 1. Твои файлы проекта
set(PROJECT_SOURCES
    "${CMAKE_SOURCE_DIR}/main.cpp"
    "${CMAKE_SOURCE_DIR}/renderer.cpp"
    "${CMAKE_SOURCE_DIR}/math_3d.cpp"
    "${CMAKE_SOURCE_DIR}/mesh.cpp"
)

# 2. Файлы ImGui (лежат там же, где заголовки)
set(IMGUI_SOURCES
    "${CMAKE_SOURCE_DIR}/dependencies/include/imgui/imgui.cpp"
    "${CMAKE_SOURCE_DIR}/dependencies/include/imgui/imgui_draw.cpp"
    "${CMAKE_SOURCE_DIR}/dependencies/include/imgui/imgui_tables.cpp"
    "${CMAKE_SOURCE_DIR}/dependencies/include/imgui/imgui_widgets.cpp"
    "${CMAKE_SOURCE_DIR}/dependencies/include/imgui/imgui_impl_glfw.cpp"
    "${CMAKE_SOURCE_DIR}/dependencies/include/imgui/imgui_impl_opengl3.cpp"
)

# 3. Загрузчик OpenGL
set(GLAD_SOURCE "${CMAKE_SOURCE_DIR}/glad.c")

# --- EXECUTABLE ---
add_executable(app ${PROJECT_SOURCES} ${IMGUI_SOURCES} ${GLAD_SOURCE})

# --- LIBRARIES ---
target_link_libraries(app PRIVATE glfw)

if(APPLE)
    target_link_libraries(app PRIVATE "-framework OpenGL")
    target_link_libraries(app PRIVATE "-framework Cocoa")
    target_link_libraries(app PRIVATE "-framework IOKit")
    target_link_libraries(app PRIVATE "-framework CoreVideo")
    target_link_libraries(app PRIVATE "-framework CoreFoundation")
endif()
