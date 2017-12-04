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
#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Window.hpp>
#include <memory>
#include <glm/mat4x4.hpp>
#include "shader.h"
#include "vertexbuffer.h"
#include "vertexarray.h"

class Application
{

public:
    Application();
    int run();

private:
    bool init();
    void draw();
    void processEvent(const sf::Event& e);
    void cleanup();
    void update(float dt); //seconds

    std::unique_ptr<sf::Window> window;
    std::unique_ptr<Shader> shader;
    VertexArray VAO;
    glm::mat4 projection;
    glm::mat4 model;
    sf::Clock time;
};

#endif // APPLICATION_H
