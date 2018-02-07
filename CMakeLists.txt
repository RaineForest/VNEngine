cmake_minimum_required(VERSION 3.0.0)

project(VNgine)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(vngine.a STATIC
	"src/init/GameInit3D.cpp"
)
