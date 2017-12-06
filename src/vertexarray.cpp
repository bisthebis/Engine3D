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
#include "vertexarray.h"
#include <glad/glad.h>
#include <stdexcept>

VertexArray::VertexArray() : enabled(false)
{

}

VertexArray::~VertexArray() {
    if (enabled)
        glDeleteVertexArrays(1, &vao);
}

VertexArray::VertexArray(VertexArray &&rhs) {
    enabled = rhs.enabled;
    vbos = std::move(rhs.vbos);
    vao = rhs.vao;
    rhs.enabled = false;
}

VertexArray& VertexArray::operator=(VertexArray &&rhs) {
    enabled = rhs.enabled;
    vbos = std::move(rhs.vbos);
    vao = rhs.vao;
    rhs.enabled = false;
    return *this;
}

void VertexArray::initEmpty() {
    if (enabled) {
        glDeleteVertexArrays(1, &vao);
        vbos.clear(); //Destroys the VBOs and call their destructor
    }

    glGenVertexArrays(1, &vao);
    enabled = true;
}

void VertexArray::bind() {
    if (enabled == false)
        throw std::runtime_error("Trying to bind an invalid VAO");

    glBindVertexArray(vao);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

void VertexArray::takeVBO(VertexBuffer &&vbo) {
    //Pushing an empty buffer then swap
    vbos.push_back(std::move(vbo));
    //vbos[vbos.size()-1] = std::move(vbo);
}
