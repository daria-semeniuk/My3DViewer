# My3DViewer

Цей проект реалізує 3D-вьювер, який може завантажувати та відображати файли STL.

## Використані технології

C++17, CMake, vcpkg, GLM, GLFW, Glad.

## Збірка

```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<шлях_до_vcpkg>/scripts/buildsystems/vcpkg.cmake
cmake --build build
./build/My3DViewer
```
