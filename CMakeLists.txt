cmake_minimum_required(VERSION 3.0.0)

project(VNgine)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.2 REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")

include_directories(${PROJECT_SOURCE_DIR}/include)

set(VNGINE_SOURCES
	"src/graphics/glwrapping/Shader.cpp"
	"src/graphics/glwrapping/ShaderProgram.cpp"
	"src/init/GameInit3D.cpp"
)

set(LIBS ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARY} glfw -ldl)

add_library(vngine STATIC ${VNGINE_SOURCES})

target_link_libraries(vngine ${LIBS})

#######################################################
####################### Testing #######################
#######################################################

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/googletest)
enable_testing()
include_directories(${PROJECT_SOURCE_DIR}/lib/googletest/googletest/include ${PROJECT_SOURCE_DIR}/lib/googletest/googletest)
include_directories(${PROJECT_SOURCE_DIR}/lib/googletest/googlemock/include ${PROJECT_SOURCE_DIR}/lib/googletest/googlemock)

set(VNGINE_TESTS
	"test/unit/main.cpp"
	"test/unit/PointTest.cpp"
	"test/unit/GLHelperTest.cpp"
)

add_executable(vngine_unit ${VNGINE_TESTS})
target_link_libraries(vngine_unit gtest gtest_main gmock gmock_main ${LIBS})
add_test(vngine_unit vngine_unit)

add_executable(vngine_render_gameinit "test/rendering/GameInitTest.cpp")
target_link_libraries(vngine_render_gameinit ${LIBS})
target_link_libraries(vngine_render_gameinit vngine)
