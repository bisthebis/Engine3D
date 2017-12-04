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


inline static void getProjection(glm::mat4& target, float width, float height, bool orthographic = false, const float zFar = 50.0f)
{
        if(!orthographic)
            target = glm::perspective(45.0f, width/height, 0.1f, zFar);
        else
            {
                float ratio = width / height;
                if(ratio >= 1)
                target = glm::ortho(-2.0f * ratio, 2.0f * ratio, -2.0f, 2.0f, -2.0f, zFar);
                else
                target = glm::ortho(-2.0f, 2.0f, -2.0f / ratio, 2.0f / ratio, -2.0f, zFar);
            }
}

void Application::updateProjection() {
    getProjection(projection, window->getSize().x, window->getSize().y);
}


Application::Application() : projection(1.0)
{
}

bool Application::init() {
    window = std::make_unique<sf::Window>(sf::VideoMode(200, 200), "SFML works!");
    if (!gladLoadGL()) {
        return false;
    }

    glClearColor(0, 0.5, 1.0, 1.0);
    glDisable(GL_CULL_FACE);

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
    updateProjection();
    model = glm::mat4(1.0);
    cam.setPosition({0,0,0});
    cam.lookAt(glm::vec3(1,0,0));

    return true;
}

void Application::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    unsigned int projectionLocation = glGetUniformLocation(shader->getProgramId(), "projection");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

    unsigned int modelLocation = glGetUniformLocation(shader->getProgramId(), "model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

    unsigned int cameraLocation = glGetUniformLocation(shader->getProgramId(), "view");
    glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, glm::value_ptr(cam.getView()));

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
        this->update(time.restart().asSeconds());
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
        updateProjection();
        glViewport(0, 0, event.size.width, event.size.height);
    }
        break;
    default:
        break;
    }
}

void Application::cleanup() {
}

void Application::update(float dt) {
    //model = glm::rotate(model, glm::radians(60.f * dt), {0,1, 0});
    cam.rotateY(glm::radians(180.f * dt));
}
