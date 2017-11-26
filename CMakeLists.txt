cmake_minimum_required(VERSION 3.7)
project(Engine3D)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(SFML COMPONENTS window system)
message(STATUS "SFML found : ${SFML_FOUND}")

include_directories(${SFML_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include)

add_executable(SFML_test main.cpp glad.c application.cpp application.h shader.h shader.cpp vertexbuffer.h vertexbuffer.cpp)

target_link_libraries(SFML_test ${SFML_LIBRARIES})

