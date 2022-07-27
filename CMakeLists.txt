cmake_minimum_required(VERSION 3.22)
project(REngine)

set(CMAKE_CXX_STANDARD 14)

add_executable(REngine glad.c main.cpp Rendering/Shader.cpp Rendering/Shader.h Rendering/ImageLoader.cpp Rendering/stb_image.h Rendering/Texture.cpp Rendering/Texture.h Rendering/Camera.cpp Rendering/Camera.h Rendering/Window.cpp Rendering/Window.h)

#Link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(REngine OpenGL::GL)

#Link glfw
find_package(glfw3 3.3 REQUIRED)
target_link_libraries(REngine glfw)

#Link glm
find_package(glm REQUIRED)
target_link_libraries(REngine glm)