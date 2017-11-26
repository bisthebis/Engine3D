#include <SFML/Window.hpp>
#include <glad/glad.h>
#include <iostream>


int main()
{
    sf::Window window(sf::VideoMode(200, 200), "SFML works!");

    if (!gladLoadGL())
    {
        std::cerr << "FATAL ERROR : couldn't load glad" << std::endl;
        return -1;
    }

    glClearColor(0, 0.5, 1.0, 1);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    float colors[] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    };

    unsigned int VBOv, VBOc;
    glGenBuffers(1, &VBOv);
    glBindBuffer(GL_ARRAY_BUFFER, VBOv);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBOc);
    glBindBuffer(GL_ARRAY_BUFFER, VBOc);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    static const char *vertexShader = "#version 330 core\n layout (location = 0) in vec3 Pos;\n layout (location = 1) in vec3 Col;\n out vec3 outColor; \n void main() { gl_Position = vec4(Pos, 1.0); outColor = Col; }";
    static const char *fragmentShader = "#version 330 core\n in vec3 outColor; \n out vec4 FragColor; \n void main() { FragColor = vec4(outColor, 1.0); }";

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex, 1, &vertexShader, nullptr);
    glCompileShader(vertex);

    glShaderSource(fragment, 1, &fragmentShader, nullptr);
    glCompileShader(fragment);

    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glBindBuffer(GL_ARRAY_BUFFER, VBOv);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOc);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }


        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        window.display();
    }

    return 0;
}
