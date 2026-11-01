cmake_minimum_required(VERSION 3.20)
project(My3DViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/ViewerWindow.h
    src/ViewerWindow.cpp
    src/Vertex.h
    src/OpenglRenderSystem.h
    src/OpenglRenderSystem.cpp
    src/GeometryPrimitives.h
    src/GeometryPrimitives.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad::glad
    glm::glm
    OpenGL::GL
)
