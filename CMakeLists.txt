cmake_minimum_required(VERSION 3.0.0)

include(ExternalProject)

project(VNgine)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.2 REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall -Wextra -Werror")

include_directories(${PROJECT_SOURCE_DIR}/include)

# Download and unpack googletest at configure time
configure_file(cmake/googletest-download.cmake googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
				 EXCLUDE_FROM_ALL)

#################################
############ Library ############
#################################

set(VNGINE_SOURCES
	"src/graphics/glwrapping/Shader.cpp"
	"src/graphics/glwrapping/ShaderProgram.cpp"
	"src/init/GameInit3D.cpp"
)

set(LIBS ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARY} glfw -ldl)

add_compile_definitions(VNGINE_OPENGL_LIB="$<IF:$<BOOL:${OPENGL_gl_LIBRARY}>,${OPENGL_gl_LIBRARY},${OPENGL_opengl_LIBRARY}>")
add_library(vngine STATIC ${VNGINE_SOURCES})
target_link_libraries(vngine ${LIBS})

#######################################################
####################### Testing #######################
#######################################################

enable_testing()

set(VNGINE_TESTS
	"test/unit/main.cpp"
	"test/unit/PointTest.cpp"
	"test/unit/GLHelperTest.cpp"
)

add_executable(vngine_unit ${VNGINE_TESTS})
target_link_libraries(vngine_unit gtest_main gmock_main vngine ${LIBS})
add_test(vngine_unit vngine_unit)

add_executable(vngine_render_gameinit "test/rendering/GameInitTest.cpp")
target_link_libraries(vngine_render_gameinit ${LIBS} vngine)

add_executable(vngine_render_triangle "test/rendering/Triangle.cpp")
target_link_libraries(vngine_render_triangle ${LIBS} vngine)
