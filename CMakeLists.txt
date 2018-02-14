cmake_minimum_required(VERSION 3.0.0)

project(VNgine)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(VNGINE_SOURCES
	"src/graphics/Shader.cpp"
	"src/graphics/ShaderProgram.cpp"
	"src/init/GameInit3D.cpp"
)

set(LIBS ${OPENGL_LIBRARY} ${GLEW_LIBRARY} ${GLFW3_LIBRARY})

add_library(vngine STATIC ${VNGINE_SOURCES})

target_link_libraries(vngine ${LIBS})
