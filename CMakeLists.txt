cmake_minimum_required(VERSION 3.7)
project(Engine3D)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(SFML COMPONENTS window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include)
    include_directories(${SFML_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include)
    add_subdirectory(src)
else ()
    error("SFML not found ! : ${SFML_FOUND}")
endif()

