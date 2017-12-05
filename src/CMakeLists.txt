set(SOURCE_FILES
    main.cpp
    glad.c
    application.cpp application.h
    shader.h shader.cpp
    vertexbuffer.h vertexbuffer.cpp
    vertexarray.h vertexarray.cpp
    camera.h camera.cpp)

add_executable(SFML_test ${SOURCE_FILES})
target_link_libraries(SFML_test ${SFML_LIBRARIES})
