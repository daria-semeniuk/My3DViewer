cmake_minimum_required(VERSION 3.10)
project(My3DViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пошук бібліотек
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# Додавання виконуваного файлу
add_executable(My3DViewer main.cpp)

# Підключення бібліотек
target_link_libraries(My3DViewer PRIVATE glfw glm::glm)
