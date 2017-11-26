/*
MIT License

Copyright (c) 2017 Boris Martin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "application.h"
#include <glad/glad.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


Application::Application() : projection(1.0)
{
}

bool Application::init() {
    window = std::make_unique<sf::Window>(sf::VideoMode(200, 200), "SFML works!");
    if (!gladLoadGL()) {
        return false;
    }

    glClearColor(0, 0.5, 1.0, 1.0);

    VertexBuffer VBO[2];

    //Vertices
    float vertices[] = {
        -0.5f, -0.5f, 1.0f,
         0.5f, -0.5f, 1.0f,
         0.0f,  0.5f, 1.0f
    };

    VBO[0] = createArrayBuffer(vertices, sizeof(vertices));

    //Colors
    float colors[] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    };

    VBO[1] = createArrayBuffer(colors, sizeof(vertices));

    VAO.initEmpty();
    VAO.bind();

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0].id());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1].id());
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    VAO.takeVBO(std::move(VBO[0]));
    VAO.takeVBO(std::move(VBO[1]));

    //Shader
    shader = makeShaderFromFile("shaders/default.vert", "shaders/default.frag");
    glUseProgram(shader->getProgramId());

    //Init projection
    projection = glm::ortho(-1.f, 1.0f, -1.0f, 1.0f, -1.0f, 1.f);

    return true;
}

void Application::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    unsigned int projectionLocation = glGetUniformLocation(shader->getProgramId(), "projection");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);

    window->display();
}

int Application::run() {

    if (init() == false)
        return -1;

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            processEvent(event);
        }

        this->draw();
    }

    cleanup();
}

void Application::processEvent(const sf::Event &event) {

    switch (event.type) {

    case sf::Event::Closed:
        window->close();
        break;
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape)
            window->close();
    case sf::Event::Resized:
    {
        float w = float(event.size.width);
        float h = float(event.size.height);
        float ratio = w/h;
        glViewport(0, 0, event.size.width, event.size.height);
        if (ratio > 1)
            projection = glm::ortho(-ratio, ratio, -1.f, 1.f, -1.0f, 1.0f);
        else
            projection = glm::ortho(-1.f, 1.f, -1.f/ratio, 1.f/ratio, -1.0f, 1.0f);

    }
        break;
    default:
        break;
    }
}

void Application::cleanup() {
}
