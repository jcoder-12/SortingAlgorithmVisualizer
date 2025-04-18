cmake_minimum_required(VERSION 3.10.0)
project(SortingAlgorithmVisualizer VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory(glfw)
find_package(OpenGL REQUIRED)

set(PROJECT_SOURCES
  src/main.cpp
)

set(IMGUI_SOURCES
  imgui/imgui.cpp
  imgui/imgui_demo.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_widgets.cpp
  imgui/imgui_tables.cpp
  imgui/backends/imgui_impl_glfw.cpp
  imgui/backends/imgui_impl_opengl3.cpp
)

set(INCLUDES
  imgui
  imgui/backends
  glfw/include
)

set(LIBRARIES
  glfw
  OpenGL::GL
)

add_executable(SortingAlgorithmVisualizer ${PROJECT_SOURCES} ${IMGUI_SOURCES})
target_include_directories(SortingAlgorithmVisualizer PRIVATE ${INCLUDES})
target_link_libraries(SortingAlgorithmVisualizer PRIVATE ${LIBRARIES})